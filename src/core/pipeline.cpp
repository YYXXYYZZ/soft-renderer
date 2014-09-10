#include "core/pipeline.h"
#include <iostream>

PipeLine::PipeLine()
{
}

void PipeLine::attachVertexShader(VertexShader *vertShader)
{
    this->vertShader = vertShader;
}

void PipeLine::attachClipper(Clipper *clipper)
{
    this->clipper = clipper;
}

void PipeLine::execute()
{
    if (!vertShader) {
        std::cerr << "Warning: null vertex shader! "<<std::endl;
        return;
    }
    vertShader->execute();
    if (!clipper) {
        std::cerr << "Warning: null clipper! "<<std::endl;
        return;
    }
    clipper->execute();
}
