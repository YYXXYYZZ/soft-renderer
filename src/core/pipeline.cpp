#include "core/pipeline.h"
#include <iostream>

Pipeline::Pipeline()
{
}

void Pipeline::attachVertexShader(VertexShader *vertShader)
{
    this->vertShader = vertShader;
}

void Pipeline::attachClipper(Clipper *clipper)
{
    this->clipper = clipper;
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
}
PipelineConfiguration Pipeline::getConfiguration() const
{
    return configuration;
}

void Pipeline::setConfiguration(const PipelineConfiguration &value)
{
    configuration = value;
}

