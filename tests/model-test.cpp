#include <iostream>
#include <GLFW/glfw3.h>

#include <core/pipeline.h>
#include <core/gpumemory.h>
#include <core/constant.h>
#include <core/vertexshader.h>
#include <core/fragshader.h>
#include <core/helper.h>
#include <glm/gtc/matrix_transform.hpp>

const int width = 500;
const int height = 500;
glm::mat4 MVP(1.0f);
PointObject *vertices;


Pipeline pl;

glm::vec3 computePerPixel(PointObject &p,Triangle &t){
    return p.getAttachVec3("color");
}

void computePerVertex(int step)
{
    glm::vec4 pos(helper::vertices[step],1);

    glm::vec3 color(helper::colors[step]);

    pos = MVP * pos;
    vertices[step].setPos(pos);
    vertices[step].setAttachVec3("color",color);
}

void initializePipeline(){

    helper::loadObj("bunny_color.obj");

    int vertexCount = helper::vertices.size();
    int vertexIndexCount  = helper::faces.size();
    std::cout <<" cout M1+ : "<< vertexCount;
    std::cout <<" cout M2+ : "<< helper::colors.size();
    std::cout <<" cout M3+ : "<< vertexIndexCount;
    int *indices;
    GPUMemory::alloc(Constant::SF_POSITION,vertexCount,vertices);
    GPUMemory::alloc(Constant::SF_POSITIONINDEX,vertexIndexCount,indices);
    GPUMemory::memoryCopy(Constant::SF_POSITIONINDEX,vertexIndexCount,&helper::faces[0]);


    glm::mat4 model = glm::rotate( glm::mat4(1.0f),45.0f,glm::vec3(1,1,1));
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f,0.0f,2.0f),
                                 glm::vec3(0.0f,0.0f,0.0f),
                                 glm::vec3(0.0f,0.1f,0.0f));
    glm::mat4 projection = glm::perspective(60.0f, (float)0.75, 0.3f, 100.0f);
////    MVP = /*projection *view **/model;


    VertexShader *vs = new VertexShader ;
    vs->setHandle(&computePerVertex);
    vs->setHandleTimes(helper::vertices.size());

    FragShader *fs = new FragShader;
    fs->setHandle(&computePerPixel);

    Pipeline::Config config;
    config.height = height;
    config.width = width;
    config.primitiveType = TRIANGLES;
    config.clearColor = glm::vec3(0.5f,0.5f,0.5f);
    config.renderByIndex = true;


    pl.setConfig(config);
    pl.attachVertShader(vs);
    pl.attachFragShader(fs);
    pl.render();
}


int main()
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(width, height, "soft renderer", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    initializePipeline();

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
//        pl.update();
        glDrawPixels(width,height,GL_RGB,GL_FLOAT,pl.getColorBuffer());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
