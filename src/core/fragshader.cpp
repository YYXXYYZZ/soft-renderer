#include "core/fragshader.h"

FragShader::FragShader()
{
}

// called once for every pixel
void FragShader::execute()
{
    initialize();
    iterationCompute(0);
}

void FragShader::setArgument()
{

}

void FragShader::initialize()
{

}

void FragShader::iterationCompute(int step)
{

}

int FragShader::iterationTimes()
{

}
