void menuin(sf::RenderWindow & window1) {

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

    window1.draw(menuBg);
    window1.draw(menu1);
    window1.draw(menu2);
    window1.draw(menu3);

    window1.display();

    getchar();

}