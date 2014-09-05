#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{

    sf::RenderWindow window(sf::VideoMode(800,600),"soft-renderer");

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);


        sf::Vertex vertex(sf::Vector2f(10,10));
        vertex.color =  sf::Color::Red;
        window.draw(&vertex,1,sf::Points);

        window.display();
    }

    return 0;
}

