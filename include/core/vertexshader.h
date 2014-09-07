#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H

#include "core/shader.h"
#include <glm/gtc/matrix_transform.hpp>

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
    int h = 600;

    glm::mat4 MVP;
};

#endif // VERTEXSHADER_H
