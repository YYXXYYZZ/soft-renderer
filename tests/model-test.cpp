#include <iostream>
#include <GLFW/glfw3.h>

#include <core/pipeline.h>
#include <core/gpumemory.h>
#include <core/constant.h>
#include <core/vertexshader.h>
#include <core/fragshader.h>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>

const int width = 500;
const int height = 500;
glm::mat4 MVP(1.0f);
PointObject *pointObjects;
std::vector<float> meshVertices;
std::vector<int> meshIndices;

Pipeline pl;

glm::vec3 computePerPixel(PointObject &p,Triangle &t){
    return p.getAttachVec3("color");
}

void computePerVertex(int step)
{
    glm::vec4 pos(meshVertices[step],
                  meshVertices[step+1],
                  meshVertices[step+2],
                  1);

//    glm::vec3 color(helper::colors[step]);

    pos = MVP * pos;
    pointObjects[step].setPos(pos);
    pointObjects[step].setAttachVec3("color",vec3(0.25f,0.37f,0.66f));
}

void initializePipeline(){



    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile("bunny_color.obj",
                                             aiProcess_CalcTangentSpace       |
                                             aiProcess_Triangulate            |
                                             aiProcess_JoinIdenticalVertices  |
                                             aiProcess_SortByPType);

    if (!scene)
    {
        std::cout << "import asset error!" << importer.GetErrorString() << std::endl;
        exit(0);
    }

    if (!scene->HasMeshes()) {
        std::cout << "the scene has no meshes!" << std::endl;
        exit(0);
    }



    for (unsigned i = 0; i < scene->mNumMeshes; ++i) {
        const aiMesh* paiMesh = scene->mMeshes[i];

        for (unsigned j = 0; j < paiMesh->mNumVertices; ++j) {
            const aiVector3D* pPos = &(paiMesh->mVertices[j]);
            meshVertices.push_back(pPos->x);
            meshVertices.push_back(pPos->y);
            meshVertices.push_back(pPos->z);
        }

        for (unsigned j = 0; j < paiMesh->mNumFaces; ++j) {
            const aiFace* pFaces = &(paiMesh->mFaces[j]);
            for (unsigned k = 0; k < pFaces->mNumIndices; ++k) {
                meshIndices.push_back(pFaces->mIndices[k]);
            }
        }
    }


    int *index;
    size_t vertexCount = meshVertices.size();
    size_t vertexIndexCount = meshIndices.size();
    GPUMemory::alloc(Constant::SF_POSITION,vertexCount,pointObjects);
    GPUMemory::alloc(Constant::SF_POSITIONINDEX,vertexIndexCount,index);
    GPUMemory::memoryCopy(Constant::SF_POSITIONINDEX,vertexIndexCount,&meshIndices[0]);


    glm::mat4 model = glm::rotate( glm::mat4(1.0f),45.0f,glm::vec3(1,1,1));
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f,0.0f,2.0f),
                                 glm::vec3(0.0f,0.0f,0.0f),
                                 glm::vec3(0.0f,0.1f,0.0f));
    glm::mat4 projection = glm::perspective(60.0f, (float)0.75, 0.3f, 100.0f);
    ////    MVP = /*projection *view **/model;


    VertexShader *vs = new VertexShader ;
    vs->setHandle(&computePerVertex);
    vs->setHandleTimes(vertexCount/3);

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

    window = glfwCreateWindow(width, height, "soft-renderer", NULL, NULL);
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
