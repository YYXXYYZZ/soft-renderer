#include "core/vertexshader.h"
#include "core/gpumemory.h"
#include "core/constant.h"

VertexShader::VertexShader()
{
}
int times;
void VertexShader::initialize()
{
    static float A[3]={
      0.5,0.5,-0.5
    };
    static float B[3]={
      -0.5,0.5,-0.5
    };
    static float C[3]={
      0.5,-0.5,-0.5
    };
    static float D[3]={
      -0.5,-0.5,-0.5
    };
    static float E[3]={
      0.5,-0.5,0.5
    };
    static float F[3]={
      0.5,0.5,0.5
    };
    static float G[3]={
      -0.5,0.5,0.5
    };
    static float H[3]={
      -0.5,-0.5,0.5
    };

    static float positions[] =
    {
       // front
        G[0],G[1],G[2],
        H[0],H[1],H[2],
        F[0],F[1],F[2],

        F[0],F[1],F[2],
        H[0],H[1],H[2],
        E[0],E[1],E[2],
        // left
        B[0],B[1],B[2],
        D[0],D[1],D[2],
        G[0],G[1],G[2],

        G[0],G[1],G[2],
        D[0],D[1],D[2],
        H[0],H[1],H[2],
        //right
        F[0],F[1],F[2],
        E[0],E[1],E[2],
        A[0],A[1],A[2],

        A[0],A[1],A[2],
        E[0],E[1],E[2],
        C[0],C[1],C[2],
        //back
        A[0],A[1],A[2],
        C[0],C[1],C[2],
        B[0],B[1],B[2],

        B[0],B[1],B[2],
        C[0],C[1],C[2],
        D[0],D[1],D[2],
        //top
        H[0],H[1],H[2],
        D[0],D[1],D[2],
        E[0],E[1],E[2],

        E[0],E[1],E[2],
        D[0],D[1],D[2],
        C[0],C[1],C[2],
        //bottom
        B[0],B[1],B[2],
        G[0],G[1],G[2],
        A[0],A[1],A[2],

        A[0],A[1],A[2],
        G[0],G[1],G[2],
        F[0],F[1],F[2],

    };

    times = sizeof(positions)/sizeof(float)/3;

    float color[] =
    {
        0.0f,0.1f,0.5f,
        0.4f,0.3f,0.2f,
        0.1f,0.4f,0.3f
    };

    GPUMemory::alloc<float>("positions",sizeof(positions)/sizeof(float),_positions.data);
    GPUMemory::alloc<float>("color",9,_color.data);
    GPUMemory::alloc<glm::vec4>(Constant::SF_POSITION,sizeof(positions)/sizeof(float),_out.data);

    GPUMemory::memoryCopy<float>("positions",sizeof(positions)/sizeof(float),positions);
    GPUMemory::memoryCopy<float>("color",9,color);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model,-45.0f,glm::vec3(0,1,0));
    model = glm::rotate(model,45.0f,glm::vec3(1,0,0));
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f,0.0f,1.0f),
                                 glm::vec3(1.0f,1.0f,1.0f),
                                 glm::vec3(0.0f,1.0f,0.0f));
    glm::mat4 projection = glm::perspective(60.0f, (float)w/h, 0.3f, 100.0f);

    MVP = /*projection * view **/ model;

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
    return times;
}
