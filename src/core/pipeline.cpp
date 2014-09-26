#include "core/pipeline.h"
#include "core/gpumemory.h"
#include "core/constant.h"
#include "core/sutherlandhodgmanclipper.h"
#include <iostream>

Pipeline::Pipeline()
{
    clipper = new SutherlandHodgmanClipper;
}

Pipeline::~Pipeline()
{
    delete clipper;
}

void Pipeline::attachVertexShader(VertexShader *vertShader)
{
    this->vertShader = vertShader;
}



void Pipeline::render()
{
    if (!vertShader) {
        std::cerr << "Warning: null vertex shader! "<<std::endl;
        return;
    }
    vertShader->execute();

    //TODO fix me :6
    primitive.setup(TRIANGLES,3);

    if (!clipper) {
        std::cerr << "Warning: null clipper! "<<std::endl;
        return;
    }

    clipper->execute();

    viewPortTransform();
}

void Pipeline::clear()
{
    GPUMemory::dealloc<Triangle>(Constant::SF_PRIMITIVESETUPOUT);

}

void Pipeline::viewPortTransform()
{
    int size;
    Triangle *data;
    if (!GPUMemory::retrieve<Triangle>(Constant::SF_CLIPOUT,size,data))
        return;
    int width = 400;
    int height = 300;
    int x = 0;
    int y = 0;
    float far = -1.0f;
    float near = 1.0f;

    for (int i = 0; i < size; ++i) {
        // for each triangle
        Triangle &tri = data[i];
        for (int var = 0; var < 3; ++var) {
            glm::vec4 &vert = *(&tri.p1+var);

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
    }
}
PipelineConfiguration Pipeline::getConfiguration() const
{
    return configuration;
}

void Pipeline::setConfiguration(const PipelineConfiguration &value)
{
    configuration = value;
}

