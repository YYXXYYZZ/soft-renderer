#include "core/zbuffer.h"
#include "core/gpumemory.h"
#include "core/primitive.h"
#include "core/constant.h"
#include "core/buffer.h"
#include <algorithm>

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
static int debug_plane = 0;
void ZBuffer::execute()
{
    if (!frameBuffer){
        std::cerr << "invalid frame buffer!" << std::endl;
        return;
    }

    int size;
    Triangle *data;
    if (!GPUMemory::retrieve<Triangle>(Constant::SF_CLIPOUT,size,data)){
        std::cerr << "failed to retrieve in ZBuffer::execute" << std::endl;
        return;
    }

    int width = frameBuffer->w;
    int height = frameBuffer->h;
    int x = 0;
    int y = 0;
    float far = -1.0f;
    float near = 1.0f;

    // TODO parallel
    for (int i = 0; i < size; ++i) {

        // for each triangle
        Triangle &originalTri = data[i];
        // skip back faces
        if (originalTri.backFacing) {
            continue;
        }

        glm::vec3 normal = originalTri.normal();
        // Ax+By+Cz+D=0 if C =0 we think the plane is far enough
        // skip
        if(normal.z==0){
            continue;
        }

        // view-port transformation
        Triangle tri= originalTri;
        for (int var = 0; var < 3; ++var) {
            glm::vec4 &vert = *(&tri.p1.pos+var);

            // perspective divide
            vert.x = vert.x / vert.w;
            vert.y = vert.y / vert.w;
            vert.z = vert.z / vert.w;

            // viewport transform
            vert.x = width/2*vert.x + x + width/2;
            vert.y = height/2*vert.y + y + height/2;
            vert.z = (far-near)/2*vert.z + (far + near)/2;
            vert.w = 1.0f;
        }


        vec2 min;
        vec2 max;
        tri.extremeValue(min,max);

        // attention: initial zValue in normalized coordinate
        // find that point
        glm::vec4 downPoint = originalTri.downPoint();
        const float zValue = downPoint.z;
        const float deltaZX = - normal.x/normal.z;
        const float deltaZY = - normal.y/normal.z;



        // TODO parallel
        // attention: scan line operate on window coordinate
        // form low y to high y(bottom to up)
        for (float scanLine = round(min.y); scanLine <= round(max.y); ++scanLine) {

            // z' = z + B/C*delta
            float z = zValue + deltaZY*(scanLine-min.y);

            // for every pixel on this scan line
            std::set<float> result;
            tri.intersect(scanLine,min.x,max.x,result);

            // one point
            if (result.size()==1) {
                float x = *result.begin();
                float zResult  = z + deltaZX * (x-min.x);
                processBuffer(x,scanLine,zResult);
            }

            // two point
            if (result.size()==2) {
                float begin = *(result.begin());
                float end = *(--result.end());
                if (begin>end)
                    std::swap(begin,end);

                // TODO: parallel
                // for each pixel between point
                for (float x = begin; x <= end; ++x) {
                    float zResult = z + deltaZX * (x-min.x);
                    processBuffer(x,scanLine,zResult);
                }

            }

        }

        debug_plane++;

    }
}

void ZBuffer::processBuffer(float x,float y,float zValue)
{
    int _x = round(x);
    int _y = round(y);

    float &z = frameBuffer->zBuffer->dataAt(_x,_y);

    static float t= 0.0f;
    if (zValue < z){
        //TODO color...
        frameBuffer->colorBuffer->dataAt(_x,_y) = glm::vec3(0.7f-debug_plane*0.1,debug_plane*0.1+0.3f,0.5f);
    }

}





