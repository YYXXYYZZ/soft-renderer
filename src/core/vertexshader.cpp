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
       // front
       0.72,0.64,0.33,
       0.91,0.24,0.67,
       0.12f,0.99f,0.34f,

       0.12f,0.99f,0.34f,
       0.91,0.24,0.67,
       0.4f,0.6f,0.77f,
       // left
       0.4f,0.3f,0.2f,
       0.2f,0.25f,0.03f,
       0.72,0.64,0.33,

       0.72,0.64,0.33,
       0.2f,0.25f,0.03f,
       0.91,0.24,0.67,
       // right
       0.12f,0.99f,0.34f,
       0.4f,0.6f,0.77f,
       0.0f,0.1f,0.5f,

       0.0f,0.1f,0.5f,
       0.4f,0.6f,0.77f,
       0.1f,0.4f,0.3f,

       // back
       0.0f,0.1f,0.5f,
       0.1f,0.4f,0.3f,
       0.4f,0.3f,0.2f,

       0.4f,0.3f,0.2f,
       0.1f,0.4f,0.3f,
       0.2f,0.25f,0.03f,
       // top
       0.91,0.24,0.67,
       0.2f,0.25f,0.03f,
       0.4f,0.6f,0.77f,

       0.4f,0.6f,0.77f,
       0.2f,0.25f,0.03f,
       0.1f,0.4f,0.3f,
       // bottom
       0.4f,0.3f,0.2f,
       0.72,0.64,0.33,
       0.0f,0.1f,0.5f,

       0.0f,0.1f,0.5f,
       0.72,0.64,0.33,
       0.4f,0.6f,0.77f
    };

    GPUMemory::alloc("positions",sizeof(positions)/sizeof(float),_positions.data);
    GPUMemory::alloc("color",sizeof(color)/sizeof(float),_color.data);


    GPUMemory::memoryCopy("positions",sizeof(positions)/sizeof(float),positions);
    GPUMemory::memoryCopy("color",sizeof(color)/sizeof(float),color);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model,-45.0f,glm::vec3(0,1,0));
    model = glm::rotate(model,-45.0f,glm::vec3(1,0,0));
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f,0.0f,1.0f),
                                 glm::vec3(1.0f,1.0f,1.0f),
                                 glm::vec3(0.0f,1.0f,0.0f));
    glm::mat4 projection = glm::perspective(60.0f, (float)w/h, 0.3f, 100.0f);

    MVP = /*projection * view * */model;

    GPUMemory::alloc(Constant::SF_POSITION,sizeof(positions)/sizeof(float),_glposition.data);

}

/**
 * @brief VertexShader::iterationCompute
 *        for each vertex
 * @param step
 */
void VertexShader::iterationCompute(int step)
{
    glm::vec4 pos(_positions.data[step*3],
                  _positions.data[step*3+1],
                  _positions.data[step*3+2],
                  1);

    pos = MVP * pos;
    _glposition.data[step] = pos;
}

int VertexShader::iterationTimes()
{
    return times;
}
