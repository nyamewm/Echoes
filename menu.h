
void menu(sf::RenderWindow & window1) {
    sf::Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
    menuTexture1.loadFromFile("images/111.png");
    menuTexture2.loadFromFile("images/222.png");
    menuTexture3.loadFromFile("images/333.png");
    menuBackground.loadFromFile("images/Penguins.jpg");
    sf::Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), menuBg(menuBackground);
    bool isMenu = 1;
    int menuNum = 0;
    menu1.setPosition(100, 30);
    menu2.setPosition(100, 90);
    menu3.setPosition(100, 150);
    menuBg.setPosition(345, 0);

    //////////////////////////////МЕНЮ///////////////////
    while (isMenu)
    {
        menu1.setColor(sf::Color::White);
        menu2.setColor(sf::Color::White);
        menu3.setColor(sf::Color::White);
        menuNum = 0;
        window1.clear(sf::Color(129, 181, 221));

        if (sf::IntRect(100, 30, 300, 50).contains(sf::Mouse::getPosition(window1))) { menu1.setColor(sf::Color::Black); menuNum = 1; }
        if (sf::IntRect(100, 90, 300, 50).contains(sf::Mouse::getPosition(window1))) { menu2.setColor(sf::Color::Black); menuNum = 2; }
        if (sf::IntRect(100, 150, 300, 50).contains(sf::Mouse::getPosition(window1))) { menu3.setColor(sf::Color::Black); menuNum = 3; }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (menuNum == 1) {
                isMenu = false;
                window1.close();
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

            }


            if (menuNum == 2) { window1.display(); while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)); }
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
