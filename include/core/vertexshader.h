#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H

#include "core/shader.h"


#include <glm/gtc/matrix_transform.hpp>

template<class T>
struct data_info{
    T *data;
    int size;
};

class Vertex;

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

    glm::mat4 MVP;
    data_info<float> _positions;
    data_info<float> _color;
    data_info<glm::vec4> _glposition;

    Vertex *vertices;
};

#endif // VERTEXSHADER_H
