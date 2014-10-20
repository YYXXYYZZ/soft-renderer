#ifndef FRAGSHADER_H
#define FRAGSHADER_H

#include "core/shader.h"

struct Triangle;
class FragShader : public Shader
{
public:
    FragShader();

    virtual void execute() override;
    void setIterationCompute(void (*iterationCompute)(float &,float &,Triangle &));

private:
    void (*iterationCompute)(float &x_window,float &y_window,Triangle &t);

    void setArgument(float *x_window, float *y_window, Triangle *t);

    float *x_window;
    float *y_window;
    Triangle *primitive;

    friend class ZBuffer;

};

#endif // FRAGSHADER_H
