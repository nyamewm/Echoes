#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
/* void m_run() {
    Player a(&window);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
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
}
 */