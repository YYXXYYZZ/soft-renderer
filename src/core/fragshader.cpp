#include "core/fragshader.h"
#include "core/vertex.h"
#include <cassert>
FragShader::FragShader()
{
}

// called once for every pixel
void FragShader::execute(PointObject *point, Triangle *t)
{
    frag_color = iterationCompute(*point,*t);
}

void FragShader::setIterationCompute(vec3 (*iterationCompute)(PointObject &,
                                                              Triangle &))
{
    this->iterationCompute = iterationCompute;
}

vec3 FragShader::fragColor() const
{
    return frag_color;
}


