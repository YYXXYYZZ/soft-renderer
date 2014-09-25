#include "core/sutherlandhodgmanclipper.h"
#include "core/gpumemory.h"
#include "core/constant.h"
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

    vector<Triangle> outPrimitive;
    // TODO
    // clip each primitive
    for (int i = 0; i < primitiveCount; ++i) {

        list<vec4> *input = new list<vec4>;
        list<vec4> *output = new list<vec4>;

        input->push_back(triangle[i].p1);
        input->push_back(triangle[i].p2);
        input->push_back(triangle[i].p3);

        for (int b = Left; b <= Far; ++b) {
            clip(*input,*output,static_cast<Boundary>(b));
            swap(input,output);
            output->clear();
        }

        if (input->size()>3) {
            polygonToTriangle(*input,outPrimitive);
        }

        if (input->size()==3) {
            Triangle tri;
            tri.p1 = input->front();
            input->pop_front();
            tri.p2 = input->front();
            input->pop_front();
            tri.p3 = input->front();
            outPrimitive.push_back(tri);
        }
        // size less than 3?
        // impossiable, skip
        delete input;
        delete output;
    }
    Triangle *data;
    GPUMemory::alloc<Triangle>(Constant::SF_CLIPOUT,outPrimitive.size(),data);
    GPUMemory::memoryCopy<Triangle>(Constant::SF_CLIPOUT,outPrimitive.size(),&outPrimitive[0]);

}


void SutherlandHodgmanClipper::clip(list<vec4> &input,
                                    list<vec4> &output,
                                    Boundary b)
{
    for (list<vec4>::iterator iter = input.begin(); iter != input.end(); ++iter) {
        vec4 begin = *iter;
        list<vec4>::iterator iter_end = iter;
        iter_end++;
        if (iter_end == input.end())
            iter_end = input.begin();
        vec4 end = *iter_end;

        // both inside, put end to output
        if (inside(begin,b) && inside(end,b))
            output.push_back(end);

        // begin outside, end inside
        // put end and intersect to output
        if ( !inside(begin,b) && inside(end,b)){
            vec4 iPoint = intersect(begin,end,b);
            // intersect point may same as begin or end point,
            // if does, skip
            if (iPoint!=begin && iPoint!=end)
                output.push_back(iPoint);
            output.push_back(end);
        }

        // begin inside, end outside
        // put intersect to output
        if (inside(begin,b) && !inside(end,b)) {
            vec4 iPoint = intersect(begin,end,b);
            // intersect point may same as begin or end point,
            // if does, skip
            if (iPoint!=begin && iPoint!=end)
                output.push_back(iPoint);
        }
    }
}

bool SutherlandHodgmanClipper::inside(vec4 p1, Boundary b)
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

vec4 SutherlandHodgmanClipper::intersect(vec4 p1,vec4 p2, Boundary b)
{
    vec4 result;

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

void SutherlandHodgmanClipper::polygonToTriangle(list<vec4> polygon,
                                                 vector<Triangle> &out)
{
    // find the most left point
    float min_x = polygon.front().x;
    list<vec4>::iterator middle;
    list<vec4>::iterator left;
    list<vec4>::iterator right;
    for (list<vec4>::iterator iter = polygon.begin(); iter != polygon.end(); ++iter) {
       if (iter->x < min_x){
           min_x = iter->x;
           middle = iter;
       }
    }
    // find left
    left = middle;
    if (left==polygon.begin()) {
        left = polygon.end();
    }
    left--;

    // find right
    right = middle;
    right++;
    if (right==polygon.end()) {
        right = polygon.begin();
    }

    // target triangle
    Triangle tri;
    tri.p1 = *left;
    tri.p2 = *middle;
    tri.p3 = *right;

    out.push_back(tri);

    // check other point inside
//    for (int i = 0; i < total; ++i) {
//        tri.inside();
        ;
//    }

    // no, delete index point and continue


    // yes, spilt to two polygon

}












