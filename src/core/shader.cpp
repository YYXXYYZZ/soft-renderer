#include <iostream>

#include "core/shader.h"

Shader::Shader()
    :reinitialize(true)
{
}

Shader::~Shader()
{

}

void Shader::execute()
{
    if(getReinitialize()){
        initialize();
        reinitialize = false;
    }
    int times = iterationTimes();
    // TODO parallel!
    for (int step = 0; step < times; ++step) {
        iterationCompute(step);
    }
}

bool Shader::getReinitialize() const
{
    return reinitialize;
}

void Shader::setReinitialize(bool value)
{
    reinitialize = value;
}

