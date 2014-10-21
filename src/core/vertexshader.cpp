#include "core/vertexshader.h"
#include "core/gpumemory.h"
#include "core/constant.h"
#include "core/vertex.h"

VertexShader::VertexShader()
{
    initialize = nullptr;
    iterationCompute = nullptr;
}

void VertexShader::execute()
{
    assert(initialize&&iterationCompute);

    initialize();
    // TODO parallel!
    for (int step = 0; step < times; ++step) {
        iterationCompute(step);
    }
}

void VertexShader::setIterationCompute(void (*iterationCompute)(int))
{
    this->iterationCompute = iterationCompute;
}

void VertexShader::setIterationTimes(int value)
{
    this->times = value;
}

