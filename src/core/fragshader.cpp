#include "core/fragshader.h"
#include "core/vertex.h"
#include <cassert>
FragShader::FragShader()
{
    point = nullptr;
    iterationCompute = nullptr;
}

// called once for every pixel
void FragShader::execute()
{
    assert(point&&primitive&&iterationCompute);

    frag_color = iterationCompute(*point,*primitive);
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

void FragShader::setArgument(PointObject *point, Triangle *t)
{
    this->point = point;
    this->primitive = t;
}


