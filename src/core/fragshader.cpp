#include "core/fragshader.h"
#include <cassert>
FragShader::FragShader()
{
    x_window = nullptr;
    y_window = nullptr;
    iterationCompute = nullptr;
}

// called once for every pixel
void FragShader::execute()
{
    assert(x_window&&y_window&&primitive&&iterationCompute);

    initialize();
    iterationCompute(*x_window,*y_window,*primitive);
}

void FragShader::setIterationCompute(void (*iterationCompute)(float &,
                                                              float &,
                                                              Triangle &))
{
    this->iterationCompute = iterationCompute;
}

void FragShader::setArgument(float *x_window, float *y_window, Triangle *t)
{
    this->x_window = x_window;
    this->y_window = y_window;
    this->primitive = t;
}


