#include "core/pipeline.h"
#include <iostream>

PipeLine::PipeLine()
{
}

void PipeLine::attachVertexShader(VertexShader *vertShader)
{
    this->vertShader = vertShader;
}

void PipeLine::execute()
{
    if (!vertShader) {
        std::cerr << "Warning: null vertex shader! "<<std::endl;
    }
    vertShader->execute();
}
