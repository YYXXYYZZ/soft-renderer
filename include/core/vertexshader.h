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
    static const int w = 800;
    static const int h = 800;

    float* _positions;
    float* _color;

    PointObject *vertices;
};

#endif // VERTEXSHADER_H
