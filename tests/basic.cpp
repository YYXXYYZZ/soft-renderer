#include <iostream>
#include <SFML/Graphics.hpp>
#include <core/pipeline.h>
#include <core/gpumemory.h>
#include <core/constant.h>
#include <GL/glew.h>
using namespace std;

int main()
{

    int width = 800;
    int height = 600;

    sf::RenderWindow window(sf::VideoMode(width,height),"soft-renderer");

    if(glewInit()!=GLEW_OK){
        cout << "error in glew";
        return 0;
    }

    VertexShader *vs = new VertexShader ;
    Pipeline pl;
    pl.attachVertexShader(vs);
    pl.render();

//    int size;
//    glm::vec4 *data;
//    GPUMemory::retrieve<glm::vec4>(Constant::SF_CLIPOUT,size,data);


//    vector<sf::Vertex> verteices;
//    for (int i = 0; i < size; ++i) {
//        sf::Vertex vertex(sf::Vector2f(data[i].x,data[i].y));
//        vertex.color =  sf::Color::Red;
//        verteices.push_back(vertex);
//    }
    int size;
    Triangle *data;
    GPUMemory::retrieve<Triangle>(Constant::SF_CLIPOUT,size,data);


    vector<sf::Vertex> verteices;
    for (int i = 0; i < size; ++i) {
        Triangle &tri = data[i];
        for (int var = 0; var < 3; ++var) {
            glm::vec4 &vert = *(&tri.p1+var);
            sf::Vertex vertex(sf::Vector2f(vert.x,vert.y));
            vertex.color =  sf::Color::Red;
            verteices.push_back(vertex);
        }

    }

    //    sf::Clock clock;
    //    clock.restart();
    while(window.isOpen()){


        window.clear(sf::Color::Black);


        window.draw(verteices.data(),verteices.size(),sf::LinesStrip);

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

            }

            if (event.type == sf::Event::Closed) {
                window.close();
            }

        }

        window.display();


        //        float fps = 1.f / clock.getElapsedTime().asSeconds();
        //        std::cout << "fps" << fps << std::endl;
        //        clock.restart();
    }

    return 0;
}

