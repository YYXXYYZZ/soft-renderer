#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H

#include "core/shader.h"

class PointObject;
class VertexShader : public Shader
{
public:
    VertexShader();

    void execute();

    // initialize will init all necessary memory and uniform variable
    // iterationTimes will return how many times iterationCompute will
    // calld. iterationCompute should be called paralleled which will
    // simulate main function in shader.
    void setIterationCompute(void (*iterationCompute)(int step));
    void setIterationTimes(int value);

private:
    void (*iterationCompute)(int step);
    int times;
};

#endif // VERTEXSHADER_H
