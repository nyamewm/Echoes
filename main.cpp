#include <iostream>
#include <SFML/Graphics.hpp>

class Player {
    sf::RenderWindow* window;
    sf::RectangleShape rectangle;
    int x, y;
    int level;
public:
    Player(sf::RenderWindow* window) {
        this->level = 0;
        this->x = 100;
        this->y = 100;
        this->window = window;
        this->rectangle.setSize(sf::Vector2f(50,50));
        this->rectangle.setOrigin(25,25);
        this->rectangle.setPosition(this->x, this->y);


    }
    void draw() {
        this->window->draw(this->rectangle);

    }
    void update(float time) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

            this->rectangle.move(0 ,-2);

        }
        else 	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            this->rectangle.move(0 ,2);
        }

        else 	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            this->rectangle.move(2 ,0);
        }
        else 	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            this->rectangle.move(-2 ,0);
        }


    }
};

int main () {
    sf::RenderWindow window(sf::VideoMode(1000,1000), "Echoes");
    Player a(&window);
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        sf::Clock clock;
        float time;
        window.setVerticalSyncEnabled(true);


        a.draw();

        clock.restart();
        time = clock.getElapsedTime().asMicroseconds();
        a.update(time);
        a.draw();





        window.display();
    }

    return 0;
}