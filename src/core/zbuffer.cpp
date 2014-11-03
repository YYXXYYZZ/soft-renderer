#include "core/zbuffer.h"
#include "core/gpumemory.h"
#include "core/primitive.h"
#include "core/constant.h"
#include "core/buffer.h"
#include "core/fragshader.h"
#include <algorithm>
#include <cmath>



#ifdef _MSC_VER

float fmax(const float &v1,const float &v2){
    return v1>v2?v1:v2;
}

float fmin(const float &v1,const float &v2){
    return v1<v2?v1:v2;
}

float round(float d)
{
  return (float)floor(d + 0.5);
}

#endif


/**
 * @brief ZBuffer::ZBuffer
 *        z-buffer take responsibility for 3 steps:
 *        1.view-port transformation
 *        2.scan line rasterization
 *        3.z-buffer algorithm
 */

ZBuffer::ZBuffer()
    :frameBuffer(nullptr)
{
}

FrameBuffer *ZBuffer::getFrameBuffer() const
{
    return frameBuffer;
}

void ZBuffer::setFrameBuffer(FrameBuffer *value)
{
    frameBuffer = value;
}

void ZBuffer::execute()
{
    if (!frameBuffer){
        std::cerr << "invalid frame buffer!" << std::endl;
        return;
    }

    if (!fragShader){
        std::cerr << "null fragment shader! "<<std::endl;
        return;
    }

    size_t size;
    Triangle *data;
    if (!GPUMemory::retrieve<Triangle>(Constant::SF_CLIPOUT,size,data)){
        std::cerr << "failed to retrieve in ZBuffer::execute" << std::endl;
        return;
    }

    int width = frameBuffer->_width;
    int height = frameBuffer->_height;
    int x = 0;
    int y = 0;
    float far = -1.0f;
    float near = 1.0f;

    // TODO parallel
    for (auto i = 0; i < size; ++i) {

        // for each triangle
        Triangle &originalTri = data[i];
        // skip back faces
        if (originalTri.backFacing) {
            continue;
        }

        glm::vec3 normal = originalTri.normal();
        // Ax+By+Cz+D=0 if C =0 we
        // think the plane is far enough
        // skip
        if(normal.z==0){
            continue;
        }

        // view-port transformation
        Triangle tri= originalTri;
        for (int var = 0; var < 3; ++var) {
            PointObject &vert = *(&tri.p1+var);

            // perspective divide
            vert.x = vert.x / vert.w;
            vert.y = vert.y / vert.w;
            vert.z = vert.z / vert.w;

            // viewport transform
            vert.x = width/2*vert.x + x + width/2;
            vert.y = height/2*vert.y + y + height/2;
            vert.z = (far-near)/2*vert.z + (far + near)/2;

            // do not change w, this will be used in interpolation
            //vert.w = 1.0f;
        }

        vec2 vec2_min;
        vec2 vec2_max;
        tri.extremum(vec2_min,vec2_max);

        // attention: initial zValue in normalized coordinate
        // find that point
        glm::vec4 downPoint = originalTri.lowestYPoint();
        const float zValue = downPoint.z;
        const float deltaZX = - normal.x/normal.z;
        const float deltaZY = - normal.y/normal.z;

        // attention: scan line operate on window coordinate
        // form low y to high y(bottom to up)
        int int_min = fmax(round(vec2_min.y),0);
        int int_max = fmin(round(vec2_max.y),height);
#pragma omp parallel for num_threads(16)
        for (auto scanLine =int_min; scanLine <int_max ;++scanLine) {

            // z' = z + B/C*delta
            float z = zValue + deltaZY*(scanLine-vec2_min.y);

            // for every pixel on this scan line
            std::set<float> result;
            tri.intersect(scanLine,vec2_min.x,vec2_max.x,result);

            // one point
            if (result.size()==1) {
                int x = *result.begin();
                float zResult  = z + deltaZX * (x-vec2_min.x);
                processBuffer(x,scanLine,zResult,tri);
            }
            // two point
            else if (result.size()==2) {
                int begin = *(result.begin());
                int end = *(--result.end());
                if (begin>end)
                    std::swap(begin,end);
                // for each pixel between point
#pragma omp parallel for
                for (auto x = begin; x <= end; ++x) {
                    float zResult = z + deltaZX * (x-vec2_min.x);
                    processBuffer(x,scanLine,zResult,tri);
                }
            }

        }

    }
}
FragShader *ZBuffer::getFragShader() const
{
    return fragShader;
}

void ZBuffer::setFragShader(FragShader *value)
{
    fragShader = value;
}

void ZBuffer::processBuffer(int _x, int _y, float zValue, Triangle &t)
{

    float &z = frameBuffer->_zBuffer->dataAt(_x,_y);

    if (zValue < z){
        z = zValue;

        PointObject point;
        point.x = (float)_x;
        point.y = (float)_y;

        PointObject::interpolate(point,t);

        fragShader->execute(&point,&t);
        auto color = fragShader->fragColor();
        frameBuffer->_colorBuffer->dataAt(_x,_y) = color;
    }

}
