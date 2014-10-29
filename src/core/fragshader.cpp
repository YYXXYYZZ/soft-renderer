#include "core/fragshader.h"
#include "core/vertex.h"

FragShader::FragShader()
{
}

// called once for every pixel
void FragShader::execute(PointObject *point, Triangle *t)
{
    frag_color = handle(*point,*t);
}

void FragShader::setHandle(vec3 (*iterationCompute)(PointObject &,
                                                    Triangle &))
{
    this->handle = iterationCompute;
}

vec3 FragShader::fragColor() const
{
    return frag_color;
}


