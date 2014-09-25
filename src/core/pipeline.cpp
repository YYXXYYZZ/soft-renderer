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
    glm::vec4 *data;
    if (!GPUMemory::retrieve<glm::vec4>(Constant::SF_CLIPOUT,size,data))
        return;
    int width = 800;
    int height = 600;
    int x = 0;
    int y = 0;
    float far = -1.0f;
    float near = 1.0f;

    for (int i = 0; i < size; ++i) {
        // perspective divide
        data[i].x = data[i].x / data[i].w;
        data[i].y = data[i].y / data[i].w;
        data[i].z = data[i].z / data[i].w;

        // viewport transform
        data[i].x = width/2*data[i].x + x + width/2;
        data[i].y = height/2*data[i].y + y + height/2;
        data[i].z = (far-near)/2*data[i].z + (far + near)/2;
        data[i].w = 1.0f;
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

