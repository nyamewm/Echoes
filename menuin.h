void menuin(sf::RenderWindow & window2) {

    std::vector <int> m1 {150, 250};
    std::vector <int> m2 {150, 300};
    std::vector <int> m3 {150, 350};

    sf::Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
    menuTexture1.loadFromFile("images/111.png");
    menuTexture2.loadFromFile("images/222.png");
    menuTexture3.loadFromFile("images/333.png");
    menuBackground.loadFromFile("images/menu.jpg");
    sf::Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), menuBg(menuBackground);
    bool isMenuin = 1;
    int menuNum = 0;
    menu1.setPosition(m1[0], m1[1]);
    menu2.setPosition(m2[0], m2[1]);
    menu3.setPosition(m3[0], m3[1]);
    menuBg.setPosition(0, 0);

    while (isMenuin) {
        menu1.setColor(sf::Color::White);
        menu2.setColor(sf::Color::White);
        menu3.setColor(sf::Color::White);
        menuNum = 0;
        window2.clear(sf::Color(129, 181, 221));

        if (sf::IntRect(m1[0], m1[1], 300, 50).contains(sf::Mouse::getPosition(window2))) {
            menu1.setColor(sf::Color::Yellow);
            menuNum = 1;
        };
        if (sf::IntRect(m2[0], m2[1], 300, 50).contains(sf::Mouse::getPosition(window2))) {
            menu2.setColor(sf::Color::Yellow);
            menuNum = 2;
        };
        if (sf::IntRect(m3[0], m3[1], 300, 50).contains(sf::Mouse::getPosition(window2))) {
            menu3.setColor(sf::Color::Yellow);
            menuNum = 3;
        };

        sf::Event event;
        while (window2.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                isMenuin = false;
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (menuNum == 1) isMenuin = false;
        }
        window2.clear();

        window2.draw(menuBg);
        window2.draw(menu1);
        window2.draw(menu2);
        window2.draw(menu3);

        window2.display();
    }
}