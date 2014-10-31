#include "core/vertexshader.h"
#include "core/gpumemory.h"
#include "core/constant.h"
#include "core/vertex.h"

VertexShader::VertexShader()
{
    iterationCompute = nullptr;
}

void VertexShader::execute()
{
    assert(iterationCompute);

#pragma omp parallel for
    for (int step = 0; step < times; ++step) {
        iterationCompute(step);
    }
}

void VertexShader::setHandle(void (*iterationCompute)(int))
{
    this->iterationCompute = iterationCompute;
}

void VertexShader::setHandleTimes(int value)
{
    this->times = value;
}

