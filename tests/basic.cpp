#include <iostream>
#include <SFML/Graphics.hpp>
#include <core/pipeline.h>
#include <core/gpumemory.h>
#include <core/constant.h>
#include <core/vertexshader.h>
#include <GL/glew.h>
using namespace std;

int main()
{

    int width = 600;
    int height = 600;

    sf::RenderWindow window(sf::VideoMode(width,height),"soft-renderer");

    if(glewInit()!=GLEW_OK){
        cout << "error in glew";
        return 0;
    }

    VertexShader *vs = new VertexShader ;
    Pipeline::Config config;
    config.height = height;
    config.width = width;
    config.primitiveType = TRIANGLES;
    config.clearColor = glm::vec3(0.0f,0.0f,0.0f);
    Pipeline pl;
    pl.setConfig(config);
    pl.attachVertShader(vs);
    pl.render();

    //sf::Clock clock;
    //clock.restart();
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

            glDrawPixels(width,height,GL_RGB,GL_FLOAT,pl.getColorBuffer());
            window.display();
        }

        //float fps = 1.f / clock.getElapsedTime().asSeconds();
        //std::cout << "fps" << fps << std::endl;
        //clock.restart();
    }

    return 0;
}

