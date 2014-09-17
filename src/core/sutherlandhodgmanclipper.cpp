#include "core/sutherlandhodgmanclipper.h"
#include <core/gpumemory.h>
#include <algorithm>

SutherlandHodgmanClipper::SutherlandHodgmanClipper()
{
}

void SutherlandHodgmanClipper::execute()
{
    Clipper::execute();
    Sutherland_Hodgman();
}

void SutherlandHodgmanClipper::Sutherland_Hodgman()
{
    if(!canClip)
        return;

    vector<glm::vec4> *input = new vector<glm::vec4>;
    vector<glm::vec4> *output = new vector<glm::vec4>;
    fillData(*input);

    for (int b = Left; b <= Far; ++b) {
        clip(*input,*output,static_cast<Boundary>(b));
        swap(input,output);
        output->clear();
    }

    for (int var = 0; var < input->size(); ++var) {
        std::cout << input->at(var).x << " ";
        std::cout << input->at(var).y  << " ";
        std::cout << input->at(var).z  << std::endl;
    }

    glm::vec4 *data;
    GPUMemory::alloc<glm::vec4>("sf_clip_output",input->size(),data);
    GPUMemory::memoryCopy<glm::vec4>("sf_clip_output",input->size(),input->data());

    delete input;
    delete output;
}

void SutherlandHodgmanClipper::fillData(vector<glm::vec4> &input)
{
    for (int i = 0; i < size; ++i) {
        input.push_back(triangle[i].p1);
        input.push_back(triangle[i].p2);
        input.push_back(triangle[i].p3);
    }
}

void SutherlandHodgmanClipper::clip(vector<glm::vec4> &input,
                                    vector<glm::vec4> &output,
                                    Boundary b)
{
    for (int i = 0; i < input.size(); ++i) {
        glm::vec4 begin = input[i];
        glm::vec4 end = input[(i+1)%input.size()];

        // both inside, put end to output
        if (inside(begin,b) && inside(end,b))
            output.push_back(end);

        // begin outside, end inside
        // put end and intersect to output
        if ( !inside(begin,b) && inside(end,b)){
            glm::vec4 iPoint = intersect(begin,end,b);
            // intersect point may same as begin or end point,
            // if does, skip
            if (iPoint!=begin && iPoint!=end)
                output.push_back(iPoint);
            output.push_back(end);
        }

        // begin inside, end outside
        // put intersect to output
        if (inside(begin,b) && !inside(end,b)) {
            glm::vec4 iPoint = intersect(begin,end,b);
            // intersect point may same as begin or end point,
            // if does, skip
            if (iPoint!=begin && iPoint!=end)
                output.push_back(iPoint);
        }
    }
}

bool SutherlandHodgmanClipper::inside(glm::vec4 p1, Boundary b)
{
    switch (b) {
    case Left:
        if(p1.x < -1.0f)
            return false;
        break;
    case Right:
        if(p1.x > 1.0f)
            return false;
        break;
    case Bottom:
        if(p1.y < -1.0f)
            return false;
        break;
    case Top:
        if(p1.y > 1.0f)
            return false;
        break;
    case Near:
        if(p1.z > 1.0f)
            return false;
        break;
    case Far:
        if(p1.z < -1.0f)
            return false;
        break;

    default:
        break;
    }
    return true;
}

glm::vec4 SutherlandHodgmanClipper::intersect(glm::vec4 p1,glm::vec4 p2, Boundary b)
{
    glm::vec4 result;

    float u;
    switch (b) {
    case Left:{
        u = (-1.0f -p1.x)/(p2.x-p1.x);
        result.x = -1.0f;
        result.y = p1.y + u*(p2.y-p1.y);
        result.z = p1.z + u*(p2.z-p1.z);
        result.w = 1.0f;
    }
        break;
    case Right:{
        u = (1.0f -p1.x)/(p2.x-p1.x);
        result.x = 1.0f;
        result.y = p1.y + u*(p2.y-p1.y);
        result.z = p1.z + u*(p2.z-p1.z);
        result.w = 1.0f;
    }
        break;
    case Bottom:{
        u = (-1.0f -p1.y)/(p2.y-p1.y);
        result.x = p1.x + u*(p2.x-p1.x);
        result.y = -1.0f;
        result.z = p1.z + u*(p2.z-p1.z);
        result.w = 1.0f;
    }
        break;
    case Top:{
        u = (1.0f -p1.y)/(p2.y-p1.y);
        result.x = p1.x + u*(p2.x-p1.x);
        result.y = 1.0f;
        result.z = p1.z + u*(p2.z-p1.z);
        result.w = 1.0f;
    }
        break;
    case Near:{
        u = (1.0f -p1.z)/(p2.z-p1.z);
        result.x = p1.x + u*(p2.x-p1.x);
        result.y = p1.y + u*(p2.y-p1.y);
        result.z = 1.0f;
        result.w = 1.0f;
    }
        break;
    case Far:{
        u = (-1.0f -p1.z)/(p2.z-p1.z);
        result.x = p1.x + u*(p2.x-p1.x);
        result.y = p1.y + u*(p2.y-p1.y);
        result.z = -1.0f;
        result.w = 1.0f;
    }
        break;
    default:
        break;
    }
    return result;
}
