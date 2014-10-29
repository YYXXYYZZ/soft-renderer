#include <iostream>
#include <SFML/Graphics.hpp>
#include <core/pipeline.h>
#include <core/gpumemory.h>
#include <core/constant.h>
#include <core/vertexshader.h>
#include <core/fragshader.h>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

static const int w = 500;
static const int h = 500;
float* _positions;
float* _color;
glm::mat4 MVP(1.0f);

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

static float color[] =
{
    // front
    0.72,0.64,0.33,
    0.91,0.24,0.67,
    0.91,0.24,0.67,

    0.91,0.24,0.67,
    0.91,0.24,0.67,
    0.72,0.64,0.33,
    // left
    0.4f,0.3f,0.2f,
    0.2f,0.25f,0.03f,
    0.72,0.64,0.33,

    0.72,0.64,0.33,
    0.2f,0.25f,0.03f,
    0.91,0.24,0.67,
    // right
    0.91,0.24,0.67,
    0.72,0.64,0.33,
    0.0f,0.1f,0.5f,

    0.0f,0.1f,0.5f,
    0.72,0.64,0.33,
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
    0.72,0.64,0.33,

    0.72,0.64,0.33,
    0.2f,0.25f,0.03f,
    0.1f,0.4f,0.3f,
    // bottom
    0.4f,0.3f,0.2f,
    0.72,0.64,0.33,
    0.0f,0.1f,0.5f,

    0.0f,0.1f,0.5f,
    0.72,0.64,0.33,
    0.72,0.64,0.33
};

int times = sizeof(positions)/sizeof(float)/3;
PointObject *vertices;

void initialize()
{
    int vertexCount = sizeof(positions)/sizeof(float)/3;
    GPUMemory::alloc(Constant::SF_POSITION,vertexCount,vertices);

    GPUMemory::alloc("positions",sizeof(positions)/sizeof(float),_positions);
    GPUMemory::alloc("color",sizeof(color)/sizeof(float),_color);

    GPUMemory::memoryCopy("positions",sizeof(positions)/sizeof(float),positions);
    GPUMemory::memoryCopy("color",sizeof(color)/sizeof(float),color);

    glm::mat4 model = glm::rotate( glm::mat4(1.0f),45.0f,glm::vec3(1,0,0));
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f,0.0f,2.0f),
                                 glm::vec3(0.0f,0.0f,0.0f),
                                 glm::vec3(0.0f,0.1f,0.0f));
    glm::mat4 projection = glm::perspective(60.0f, (float)0.75, 0.3f, 100.0f);
    MVP = projection *view *model;

}

glm::vec3 FragShaderIterCompute(PointObject &p,Triangle &t){
    return p.getAttachVec3("color");
}

void iterationCompute(int step)
{
    glm::vec4 pos(_positions[step*3],
            _positions[step*3+1],
            _positions[step*3+2],
            1);

    glm::vec3 color(_color[step*3],
            _color[step*3+1],
            _color[step*3+2]);

    pos = MVP * pos;
    vertices[step].setPos(pos);
    vertices[step].setAttachVec3("color",color);
}

int main()
{

    int width = 500;
    int height = 500;

    sf::RenderWindow window(sf::VideoMode(width,height),"soft-renderer");

    if(glewInit()!=GLEW_OK){
        cout << "error in glew";
        return 0;
    }

    initialize();

    VertexShader *vs = new VertexShader ;
    vs->setIterationCompute(&iterationCompute);
    vs->setIterationTimes(times);

    FragShader *fs = new FragShader;
    fs->setIterationCompute(&FragShaderIterCompute);

    Pipeline::Config config;
    config.height = height;
    config.width = width;
    config.primitiveType = TRIANGLES;
    config.clearColor = glm::vec3(0.0f,0.0f,0.0f);

    Pipeline pl;
    pl.setConfig(config);
    pl.attachVertShader(vs);
    pl.attachFragShader(fs);
    pl.render();

//    sf::Clock clock;
//    clock.restart();
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::MouseButtonPressed){

                int x = event.mouseButton.x;
                int y = event.mouseButton.y;

                vector< unsigned char > pixels( 1 * 1 * 4 );
                glReadPixels(x,height-y,1,1,GL_RGBA,
                             GL_UNSIGNED_BYTE,
                             &pixels[0]);
                cout << "r: " << (int)pixels[0] << endl;
                cout << "g: " << (int)pixels[1] << endl;
                cout << "b: " << (int)pixels[2] << endl;
                cout << "a: " << (int)pixels[3] << endl;
                cout << endl;
                cout << "x: " << x << endl;
                cout << "y: " << 800-y << endl;
                cout << endl;

            }

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }

            if (event.type == sf::Event::KeyPressed) {

                glm::vec4 col(0);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    col.x -= 0.05f;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                   col.x += 0.05f;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    col.y += 0.05f;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    col.y -= 0.05f;
                }

                glm::mat4 translate = glm::translate(glm::mat4(1),vec3(col));
                MVP = translate * MVP;
                pl.update();
            }
            glDrawPixels(width,height,GL_RGB,GL_FLOAT,pl.getColorBuffer());
            window.display();
        }

//        float fps = 1.f / clock.getElapsedTime().asSeconds();
//        std::cout << "fps" << fps << std::endl;
//        clock.restart();
    }


    delete vs;
    delete fs;

    return 0;
}

