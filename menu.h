#include "map.h"
#include "menuin.h"
#include <sstream>

bool CollisionCircleRectangle(Dynamic object, Static obstacle)
{
    float x1 = object.pos.x;
    float y1 = object.pos.y;
    float r = object.r;
    float x2 = obstacle.rectangle.getPosition().x;
    float y2 = obstacle.rectangle.getPosition().y;
    float l = obstacle.rectangle.getSize().x;
    float w = obstacle.rectangle.getSize().y;
    float b = -2*y1;
    float c = pow(y1, 2) + pow((x2-x1), 2) - pow(r, 2);
    double D = pow(b, 2) - 4*c;
    if(D >= 0) {
        float y3 = (-b + sqrt(D)) / 2;
        float y4 = (-b - sqrt(D)) / 2;
        if(((y3 > y2)&&(y3 < y2 + w))||((y4 > y2)&&(y4 < y2 + w)))
            return true;
    }
    b = -2*y1;
    c = pow(y1, 2) + pow((x2+l-x1), 2) - pow(r, 2);
    D = pow(b, 2) - 4*c;
    if(D >= 0) {
        float y3 = (-b + sqrt(D)) / 2;
        float y4 = (-b - sqrt(D)) / 2;
        if(((y3 > y2)&&(y3 < y2 + w))||((y4 > y2)&&(y4 < y2 + w)))
            return true;
    }
    b = -2*x1;
    c = pow(x1, 2) + pow((y2-y1), 2) - pow(r, 2);
    D = pow(b, 2) - 4*c;
    if(D >= 0) {
        float x3 = (-b + sqrt(D)) / 2;
        float x4 = (-b - sqrt(D)) / 2;
        if(((x3 > y2)&&(x3 < x2 + l))||((x4 > x2)&&(x4 < x2 + l)))
            return true;
    }
    b = -2*x1;
    c = pow(x1, 2) + pow((y2+w-y1), 2) - pow(r, 2);
    D = pow(b, 2) - 4*c;
    if(D >= 0) {
        float x3 = (-b + sqrt(D)) / 2;
        float x4 = (-b - sqrt(D)) / 2;
        if(((x3 > y2)&&(x3 < x2 + l))||((x4 > x2)&&(x4 < x2 + l)))
            return true;
    }
    return false;
};

bool PointInsideRectangle(Dynamic object, Static obstacle){
    if((obstacle.rectangle.getPosition().x < object.rectangle.getPosition().x)&&
    (object.rectangle.getPosition().x < obstacle.rectangle.getPosition().x + obstacle.rectangle.getSize().x)&&
    (obstacle.rectangle.getPosition().y < object.rectangle.getPosition().y)&&
    (object.rectangle.getPosition().y < obstacle.rectangle.getPosition().y + obstacle.rectangle.getSize().y)){
        return true;
    }
    return false;
};

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

                Player player(&window);
                player.healthmax = 100;
                player.health = 100;
                player.energy = 100;
                player.energymax = 100;

                Static obstacle(&window);
                obstacle.rectangle.setPosition(200,200);

                Static nameplate(&window);
                nameplate.rectangle.setPosition(-100,-100);
                nameplate.rectangle.setFillColor(sf::Color(255,183,72));
                nameplate.rectangle.setOutlineColor(sf::Color(128,91,36));

                Static borders(&window);
                borders.rectangle.setSize(sf::Vector2f(1000, 1000));
                borders.rectangle.setPosition(sf::Vector2f(-500, -500));
                borders.rectangle.setFillColor(sf::Color(0,0,0,0));
                borders.rectangle.setOutlineThickness(15);

                Static lightning(&window);
                lightning.rectangle.setSize(sf::Vector2f(borders.rectangle.getSize().x+100, borders.rectangle.getSize().y+100));
                lightning.rectangle.setPosition(borders.rectangle.getPosition().x-50, borders.rectangle.getPosition().x-50);
                lightning.rectangle.setFillColor(sf::Color(0,0,0,0));
                lightning.rectangle.setOutlineThickness(0);

                Static message(&window);
                message.rectangle.setSize(sf::Vector2f(800-20, 175-10));
                message.rectangle.setFillColor(sf::Color(255,171,0));
                message.rectangle.setOutlineColor(sf::Color(128,86,0));

                Static healthbar(&window);
                healthbar.rectangle.setSize(sf::Vector2f(50, 10));
                healthbar.rectangle.setFillColor(sf::Color(0,0,0));
                healthbar.rectangle.setOutlineColor(sf::Color(0,128,0));
                healthbar.rectangle.setOutlineThickness(-2);

                Static healthbarInside(&window);
                healthbarInside.rectangle.setSize(sf::Vector2f(46, 6));
                healthbarInside.rectangle.setFillColor(sf::Color(0,255,0));
                healthbarInside.rectangle.setOutlineThickness(0);

                Static energybar(&window);
                energybar.rectangle.setSize(sf::Vector2f(50, 10));
                energybar.rectangle.setFillColor(sf::Color(0,0,0));
                energybar.rectangle.setOutlineColor(sf::Color(0,128,128));
                energybar.rectangle.setOutlineThickness(-2);

                Static energybarInside(&window);
                energybarInside.rectangle.setSize(sf::Vector2f(46, 6));
                energybarInside.rectangle.setFillColor(sf::Color(0,255,255));
                energybarInside.rectangle.setOutlineThickness(0);

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
                sf::Text textmessage("", font, 20);
                sf::Text texthealth("", font, 10);
                sf::Text textenergy("", font, 10);

                std::ostringstream playerVelocity;
                std::ostringstream fps;
                std::ostringstream tickrate;
                std::ostringstream health;
                std::ostringstream energy;

                float camerax;
                float cameray;


                while(window.isOpen())
                {

                    float time = clock.getElapsedTime().asSeconds();
                    float time1 = clock.getElapsedTime().asMicroseconds();
                    clock.restart();
                    timer += time;



                    if (time1 > delay) {
                        if(CollisionCircleRectangle(player, obstacle)||
                        CollisionCircleRectangle(player, borders)){
                            if(player.v > 0.5*player.vmax)
                            {
                                if(player.health/player.healthmax > 0.5*(player.v/player.vmax))
                                {
                                    player.health -= 0.5*(player.v*player.healthmax)/player.vmax;
                                }
                                else
                                    player.health = 0;
                            }
                            player.v = 0;
                        }
                        lightning.rectangle.setFillColor(sf::Color(0,0,0, 100*(-cos(timer*6.28/60)+1)));
                        player.update(time1, timer);
                        health.str(std::string());
                        health << round(player.health*100/player.healthmax);
                        energy.str(std::string());
                        energy << round(player.energy*100/player.energymax);
                        tickrate.str(std::string());
                        tickrate << 1000000/time1;		//делим миллион микросекунд на время одного апдейта
                        fps.str(std::string());
                        fps << 1000000/time1;		//делим секунду на время одной прорисовки
                        window.clear(); // рисуется всё, кроме карты
                        run(&window);

                        //observation.setCenter(player.rectangle.getPosition());
                        camerax = player.rectangle.getPosition().x;
                        cameray = player.rectangle.getPosition().y;
                        if(player.rectangle.getPosition().x < borders.rectangle.getPosition().x + 400-20)
                            camerax = borders.rectangle.getPosition().x + 400-20;
                        if(player.rectangle.getPosition().x > borders.rectangle.getPosition().x+borders.rectangle.getSize().x - 400+20)
                            camerax = borders.rectangle.getPosition().x+borders.rectangle.getSize().x - 400+20;
                        if(player.rectangle.getPosition().y < borders.rectangle.getPosition().y + 225-20)
                            cameray = borders.rectangle.getPosition().y + 225-20;
                        if(player.rectangle.getPosition().y > borders.rectangle.getPosition().y+borders.rectangle.getSize().y - 225+20)
                            cameray = borders.rectangle.getPosition().y+borders.rectangle.getSize().y - 225+20;
                        observation.setCenter(camerax, cameray);

                        message.rectangle.setPosition(player.rectangle.getPosition().x-400+10, player.rectangle.getPosition().y+50);
                        textmessage.setPosition(message.rectangle.getPosition().x+25, message.rectangle.getPosition().y+25);
                        healthbar.rectangle.setPosition(player.rectangle.getPosition().x - 25, player.rectangle.getPosition().y - 60);
                        healthbarInside.rectangle.setSize(sf::Vector2f((player.health/player.healthmax)*46,6));
                        healthbarInside.rectangle.setPosition(healthbar.rectangle.getPosition().x+2,healthbar.rectangle.getPosition().y+2);
                        energybar.rectangle.setPosition(player.rectangle.getPosition().x - 25, player.rectangle.getPosition().y - 50);
                        energybarInside.rectangle.setSize(sf::Vector2f((player.energy/player.energymax)*46,6));
                        energybarInside.rectangle.setPosition(energybar.rectangle.getPosition().x+2,energybar.rectangle.getPosition().y+2);

                        window.setView(observation);
                        window.draw(borders);
                        window.draw(obstacle);
                        window.draw(nameplate);
                        window.draw(player);
                        window.draw(healthbar);
                        window.draw(healthbarInside);
                        window.draw(energybar);
                        window.draw(energybarInside);
                        window.draw(lightning);

                        playerVelocity.str(std::string());
                        playerVelocity << (player.v)/(player.vmax);		//занесли в нее отношение скорости к максимальной скорости
                        textV.setString("V =" + playerVelocity.str());//задаем строку тексту и вызываем сформированную выше строку методом .str()
                        textV.setPosition(observation.getCenter().x - 350, observation.getCenter().y - 200);//задаем позицию текста, отступая от центра камеры
                        textFPS.setString("FPS =" + fps.str());
                        textFPS.setPosition(observation.getCenter().x - 350, observation.getCenter().y - 170);
                        texttickrate.setString("tickrate =" + tickrate.str());
                        texttickrate.setPosition(observation.getCenter().x - 350, observation.getCenter().y - 140);
                        texthealth.setString(health.str() + "%");
                        texthealth.setPosition(healthbar.rectangle.getPosition().x+14, healthbar.rectangle.getPosition().y-2);
                        textenergy.setString(energy.str() + "%");
                        textenergy.setPosition(energybar.rectangle.getPosition().x+14, energybar.rectangle.getPosition().y-2);

                        window.draw(texthealth);
                        window.draw(textenergy);
                        window.draw(textV);//рисую этот текст
                        window.draw(textFPS);
                        window.draw(texttickrate);

                        if(PointInsideRectangle(player, nameplate))
                        {
                            textmessage.setString("Hello, world!");
                            window.draw(message);
                            window.draw(textmessage);
                        }

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