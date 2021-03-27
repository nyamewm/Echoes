#include "map.h"
#include "menuin.h"



void menu(sf::RenderWindow & window1) {

    std::vector <int> m1 {150, 250};
    std::vector <int> m2 {150, 300};
    std::vector <int> m3 {150, 350};

    sf::Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
    menuTexture1.loadFromFile("images/111.png");
    menuTexture2.loadFromFile("images/222.png");
    menuTexture3.loadFromFile("images/333.png");
    menuBackground.loadFromFile("images/menu.jpg");
    sf::Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), menuBg(menuBackground);
    bool isMenu = 1;
    int menuNum = 0;
    menu1.setPosition(m1[0] , m1[1]);
    menu2.setPosition(m2[0], m2[1]);
    menu3.setPosition(m3[0], m3[1]);
    menuBg.setPosition(0, 0);

    //////////////////////////////МЕНЮ///////////////////
    while (isMenu)
    {
        menu1.setColor(sf::Color::White);
        menu2.setColor(sf::Color::White);
        menu3.setColor(sf::Color::White);
        menuNum = 0;
        window1.clear(sf::Color(129, 181, 221));

        if (sf::IntRect(m1[0] , m1[1], 300, 50).contains(sf::Mouse::getPosition(window1))) { menu1.setColor(sf::Color::Yellow); menuNum = 1; }
        if (sf::IntRect(m2[0], m2[1], 300, 50).contains(sf::Mouse::getPosition(window1))) { menu2.setColor(sf::Color::Yellow); menuNum = 2; }
        if (sf::IntRect(m3[0], m3[1], 300, 50).contains(sf::Mouse::getPosition(window1))) { menu3.setColor(sf::Color::Yellow); menuNum = 3; }

        sf::Event event;
        while (window1.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window1.close();
                isMenu = false;
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (menuNum == 1) {
                isMenu = false;
                window1.close();
                sf::RenderWindow window(sf::VideoMode(1920, 1080), "Echoes");
                Player a(&window);

                sf::Clock clock;
                float timer = 0, delay = 0.03;
                sf::View observation;
                observation.setCenter(sf::Vector2f(100.f, 100.f));
                observation.setSize(sf::Vector2f(200.f, 200.f));


                while(window.isOpen())
                {
                    float time = clock.getElapsedTime().asSeconds();
                    clock.restart();
                    timer += time;

                    if (timer > delay) {
                        timer = 0;
                        window.clear(); // рисуется всё, кроме карты
                        run(&window);



                        window.draw(a);
                        observation.setCenter(a.pos);
                        window.setView(observation);
                        window.display();
                    }


                    sf::Event event;
                    while(window.pollEvent(event))
                    {
                        if(event.type == sf::Event::Closed)
                            window.close();
                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                            sf::RenderWindow window2(sf::VideoMode(740, 500), "Echoes|pause");
                            menuin(window2, isMenu, window);
                        }
                    }

                    sf::Clock clock1;
                    float time1;
                    clock1.restart();
                    time1 = clock1.getElapsedTime().asMicroseconds();
                    a.update(time1);
                }

            }


            if (menuNum == 2) {}
            if (menuNum == 3)  { window1.close(); isMenu = false; }

        }

        window1.draw(menuBg);
        window1.draw(menu1);
        window1.draw(menu2);
        window1.draw(menu3);

        window1.display();
    }
    ////////////////////////////////////////////////////
}
