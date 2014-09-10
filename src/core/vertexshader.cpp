#include "core/vertexshader.h"
#include "core/gpumemory.h"

VertexShader::VertexShader()
{
}

void VertexShader::initialize()
{

    int positions[] =
    {
        -1,-1,0,
        1,1,0,
        -1,1,0
    };

    float color[] =
    {
        0.0f,0.1f,0.5f,
        0.4f,0.3f,0.2f,
        0.1f,0.4f,0.3f
    };

    GPUMemory::alloc<int>("positions",9,_positions.data);
    GPUMemory::alloc<float>("color",9,_color.data);
    GPUMemory::alloc<float>("gl_position",12,_out.data);

    GPUMemory::memoryCopy<int>("positions",9,positions);
    GPUMemory::memoryCopy<float>("color",9,color);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f,0.0f,-1.0f),
                                 glm::vec3(0.0f,0.0f,0.0f),
                                 glm::vec3(0.0f,1.0f,0.0f));
    glm::mat4 projection = glm::perspective(60.0f, (float)w/h, 0.3f, 100.0f);

    MVP = projection * view * model;

}


void VertexShader::iterationCompute(int step)
{
    glm::vec4 pos(_positions.data[step*3],
                  _positions.data[step*3+1],
                  _positions.data[step*3+2],
                  1);

    pos = MVP * pos;
    _out.data[step*4] = pos[0];
    _out.data[step*4+1] = pos[1];
    _out.data[step*4+2] = pos[2];
    _out.data[step*4+3] = pos[3];
}

int VertexShader::iterationTimes()
{
    return 3;
}
