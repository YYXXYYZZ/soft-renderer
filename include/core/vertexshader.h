#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H

#include "core/shader.h"

class PointObject;
class VertexShader : public Shader
{
public:
    VertexShader();
protected:
    void initialize();
    void iterationCompute(int step);
    int iterationTimes();
private:
    int w = 800;
    int h = 800;

    float* _positions;
    float* _color;

    PointObject *vertices;
};

#endif // VERTEXSHADER_H
