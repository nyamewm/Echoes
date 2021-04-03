#include "map.h"
#include "menuin.h"
#include <sstream>



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
                float timer = 0, delay = 0.0133;
                sf::View observation;

                observation.setSize(sf::Vector2f(800.f, 450.f));

                sf::Font font;//шрифт
                font.loadFromFile("arial.ttf");//передаем нашему шрифту файл шрифта
                sf::Text textV("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
                textV.setColor(sf::Color::White);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
                //text.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
                sf::Text textFPS("", font, 20);
                sf::Text texttickrate("", font, 20);

                std::ostringstream playerVelocity;    // объявили переменную
                std::ostringstream fps;    // объявили переменную
                std::ostringstream tickrate;    // объявили переменную


                while(window.isOpen())
                {

                    float time = clock.getElapsedTime().asSeconds();
                    float time1 = clock.getElapsedTime().asMicroseconds();
                    clock.restart();
                    timer += time;

                    a.update(1*time1);

                    if (timer > delay) {
                        tickrate.str(std::string());
                        tickrate << 1000000/time1;		//делим миллион микросекунд на время одного апдейта
                        fps.str(std::string());
                        fps << 1/timer;		//делим секунду на время одной прорисовки
                        timer = 0;
                        window.clear(); // рисуется всё, кроме карты
                        run(&window);


                        observation.setCenter(a.pos);
                        window.setView(observation);
                        window.draw(a);

                        playerVelocity.str(std::string());
                        playerVelocity << (a.v)/(a.vmax);		//занесли в нее отношение скорости к максимальной скорости
                        textV.setString("V =" + playerVelocity.str());//задаем строку тексту и вызываем сформированную выше строку методом .str()
                        textV.setPosition(observation.getCenter().x - 350, observation.getCenter().y - 200);//задаем позицию текста, отступая от центра камеры
                        textFPS.setString("FPS =" + fps.str());
                        textFPS.setPosition(observation.getCenter().x - 350, observation.getCenter().y - 170);
                        texttickrate.setString("tickrate =" + tickrate.str());
                        texttickrate.setPosition(observation.getCenter().x - 350, observation.getCenter().y - 140);
                        window.draw(textV);//рисую этот текст
                        window.draw(textFPS);
                        window.draw(texttickrate);

                        window.display();



                    }


                    sf::Event event;
                    while(window.pollEvent(event))
                    {
                        if(event.type == sf::Event::Closed)
                            window.close();
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                            sf::RenderWindow window2(sf::VideoMode(740, 500), "Echoes|pause");
                            //menuin(window2);
                        }
                    }


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