#include <iostream>

#include "core/shader.h"

Shader::Shader()
{
}

Shader::~Shader()
{

}

void Shader::execute()
{
    initialize();
    int times = iterationTimes();
    // TODO parallel!
    for (int step = 0; step < times; ++step) {
        iterationCompute(step);
    }
}

