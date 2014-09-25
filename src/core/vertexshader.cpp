#include "core/vertexshader.h"
#include "core/gpumemory.h"
#include "core/constant.h"

VertexShader::VertexShader()
{
}

void VertexShader::initialize()
{

    float positions[] =
    {
        -0.5,-0.5,0,
        0.5,0.5,0,
        -0.5,0.5,0,
        -0.5,-0.5,0,
        0.5,0.5,0,
        0.5,-0.5,0
    };

    float color[] =
    {
        0.0f,0.1f,0.5f,
        0.4f,0.3f,0.2f,
        0.1f,0.4f,0.3f
    };

    GPUMemory::alloc<float>("positions",2*9,_positions.data);
    GPUMemory::alloc<float>("color",9,_color.data);
    GPUMemory::alloc<glm::vec4>(Constant::SF_POSITION,6,_out.data);

    GPUMemory::memoryCopy<float>("positions",2*9,positions);
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
    _out.data[step] = pos;
}

int VertexShader::iterationTimes()
{
    return 6;
}
