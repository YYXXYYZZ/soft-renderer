#include "core/vertexshader.h"

#include "core/global.h"


extern GPUMemory GlobalGPUMemory;

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

    GlobalGPUMemory.alloc("positions",9,Int);
    GlobalGPUMemory.alloc("color",9,Float);
    GlobalGPUMemory.alloc("out",9,Int);

    MemoryInfo positions_info;
    MemoryInfo color_info;
    MemoryInfo out_info;

    GlobalGPUMemory.memoryCopy("positions",9,positions);
//    GlobalGPUMemory.memoryCopy("color",Float,sizeof(color),static_cast<void *>(color));

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f,0.0f,-1.0f),
                                 glm::vec3(0.0f,0.0f,0.0f),
                                 glm::vec3(0.0f,1.0f,0.0f));
    glm::mat4 projection = glm::perspective(60.0f, (float)w/h, 0.3f, 100.0f);

    MVP = projection * view * model;
}


void VertexShader::iterationCompute(int step)
{
//    glm::vec4 pos(positions[step*3],
//                  positions[step*3+1],
//                  positions[step*3+2],
//                  1);

//    pos = MVP * pos;
//    out[step*3] = pos[0];
//    out[step*3+1] = pos[1];
//    out[step*3+2] = pos[2];
}

int VertexShader::iterationTimes()
{
    return 3;
}
