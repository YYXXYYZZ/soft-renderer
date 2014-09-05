#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H

#include "core/shader.h"
class VertexShader : public Shader
{
public:
    VertexShader();

protected:

    void initialize();
    void iterationCompute(int step);
    int iterationTimes();

private:

};

#endif // VERTEXSHADER_H
