#include "map.h"
#include "menuin.h"
#include <sstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>
#include <vector>

const float pi = 3.1416;

bool CollisionCircleRectangle(Dynamic object, Static obstacle)
{
    float t = obstacle.rectangle.getRotation()*pi/180;
    double x1 = object.pos.x;
    double y1 = object.pos.y;
    double r = object.r;
    double x2 = obstacle.rectangle.getPosition().x;
    double y2 = obstacle.rectangle.getPosition().y;
    double m = x2-x1;
    double n = y2-y1;
    double x = m*cos(t) + n*sin(t) - obstacle.rectangle.getOrigin().x;
    double y = n*cos(t) - m*sin(t) - obstacle.rectangle.getOrigin().y;
    double l = obstacle.rectangle.getSize().x;
    double w = obstacle.rectangle.getSize().y;
    double c;
    if(abs(x)<r)
    {
        c = sqrt(r*r - x*x);
        if(((y < c)&&(c < y+w))||((y < -c)&&(-c < y+w)))
            return true;
    }
    if(abs(x+l)<r)
    {
        c = sqrt(r*r - (x+l)*(x+l));
        if(((y < c)&&(c < y+w))||((y < -c)&&(-c < y+w)))
            return true;
    }
    if(abs(y)<r)
    {
        c = sqrt(r*r - y*y);
        if(((x < c)&&(c < x+l))||((x < -c)&&(-c < x+l)))
            return true;
    }
    if(abs(y+w)<r)
    {
        c = sqrt(r*r - (y+w)*(y+w));
        if(((x < c)&&(c < x+l))||((x < -c)&&(-c < x+l)))
            return true;
    }
    return false;
};

void ResolveCollisionDynamicObstacle(Dynamic *object, Static obstacle)
{
    float t = obstacle.rectangle.getRotation()*pi/180;
    double x1 = object->pos.x;
    double y1 = object->pos.y;
    double r = object->r;
    double x2 = obstacle.rectangle.getPosition().x;
    double y2 = obstacle.rectangle.getPosition().y;
    double m = x2-x1;
    double n = y2-y1;
    double x = m*cos(t) + n*sin(t) - obstacle.rectangle.getOrigin().x;
    double y = n*cos(t) - m*sin(t) - obstacle.rectangle.getOrigin().y;
    double l = obstacle.rectangle.getSize().x;
    double w = obstacle.rectangle.getSize().y;
    double c;
    sf::Vector2f v;
    if(abs(x)<r)
    {
        c = sqrt(r*r - x*x);
        if(((y < c)&&(c < y+w))||((y < -c)&&(-c < y+w))) {
            v.x = object->v.x * cos(object->v.y*pi/180 - t);
            if((object->v.y - t*180/pi)>180)
                v.y = (t*180/pi)+180;
            else
                v.y = t*180/pi;
            object->v = v;
        }
    }
    if(abs(x+l)<r)
    {
        c = sqrt(r*r - (x+l)*(x+l));
        if(((y < c)&&(c < y+w))||((y < -c)&&(-c < y+w))) {
            v.x = object->v.x * cos(object->v.y*pi/180 - t);
            if((object->v.y - t*180/pi)>180)
                v.y = t*180/pi;
            else
                v.y = t*180/pi;
            object->v = v;
        }
    }
    if(abs(y)<r)
    {
        c = sqrt(r*r - y*y);
        if(((x < c)&&(c < x+l))||((x < -c)&&(-c < x+l))) {
            v.x = object->v.x * cos(object->v.y*pi/180 - t - (pi/2));
            if((object->v.y - t*180/pi)>180)
                v.y = t*180/pi+180;
            else
                v.y = t*180/pi;
            object->v = v;
        }
    }
    if(abs(y+w)<r)
    {
        c = sqrt(r*r - (y+w)*(y+w));
        if(((x < c)&&(c < x+l))||((x < -c)&&(-c < x+l))) {
            v.x = object->v.x * cos(object->v.y*pi/180 - t - (pi/2));
            if((object->v.y - t*180/pi)>180)
                v.y = t*180/pi;
            else
                v.y = t*180/pi+180;
            object->v = v;
        }
    }
};

bool CollisionCircleCircle(Dynamic object1, Dynamic object2)
{
    sf::Vector2f pos1 (object1.pos.x, object1.pos.y);
    sf::Vector2f pos2 (object2.pos.x, object2.pos.y);
    if((((pos1.x - pos2.x)*(pos1.x - pos2.x))+((pos1.y - pos2.y)*(pos1.y - pos2.y))) < (object1.r + object2.r)*(object1.r + object2.r))
        return true;
    else
        return false;
}

bool PointInsideRectangle(Dynamic object, Static obstacle){
    if((obstacle.rectangle.getPosition().x < object.rectangle.getPosition().x)&&
    (object.rectangle.getPosition().x < obstacle.rectangle.getPosition().x + obstacle.rectangle.getSize().x)&&
    (obstacle.rectangle.getPosition().y < object.rectangle.getPosition().y)&&
    (object.rectangle.getPosition().y < obstacle.rectangle.getPosition().y + obstacle.rectangle.getSize().y)){
        return true;
    }
    return false;
};

void TurretUpdate (Turret *turret, Dynamic object, float time, float timer, std::ostringstream *text, sf::RenderWindow* window, std::vector<Bullet*>* BulletDrawList) {
    if(object.alive){
        sf::Vector2f objectPosition = object.rectangle.getPosition();
        sf::Vector2f turretPosition = turret->rectangle.getPosition();
        float currentAngle = turret->rectangle.getRotation()*(2*3.14/360);
        float dx = objectPosition.x-turretPosition.x;
        float dy = objectPosition.y-turretPosition.y;
        float neededAngle;
        float arctan = atan(dy/dx);
        if(dx > 0)
        {
            if(arctan < 0)
                neededAngle = 6.28 + arctan;
            else
                neededAngle = arctan;
        }
        else
            neededAngle = 3.14 + arctan;
        text->str(std::string());
        *text << neededAngle;
        if(abs(currentAngle-neededAngle) > 0.044)
        {
            if(currentAngle < neededAngle)
            {
                if ((neededAngle - currentAngle) < 3.14)
                    turret->rectangle.rotate(turret->vrot * time);
                else
                    turret->rectangle.rotate(-turret->vrot * time);
            }
            else
            {
                if ((currentAngle - neededAngle) < 3.14)
                    turret->rectangle.rotate(-turret->vrot * time);
                else
                    turret->rectangle.rotate(turret->vrot * time);
            }
        }
        if((((dx*dx)+(dy*dy)) < 200*200)&&((timer - turret->lastshot) > turret->reload)) {
            BulletDrawList->push_back(new Bullet(window, *turret, timer));
            turret->lastshot = timer;
            turret->shoot.play();
        }
    }
};

void death(Dynamic *object){
    object->health = 0;
    object->alive = false;
    object->rectangle.setTexture(object->pTextureExplosion);
    object->rectangle.setScale(2,2);
    object->explosion.play();
}

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
                player.health = player.healthmax;
                player.energymax = 100;
                player.energy = player.energymax;

                Static obstacle(&window);
                obstacle.rectangle.setPosition(200,200);
                obstacle.rectangle.setRotation(45);

                Static testobstacle(&window);
                testobstacle.rectangle.setPosition(1000,1000);

                Static nameplate(&window);
                nameplate.rectangle.setPosition(-100,-100);
                nameplate.rectangle.setSize(sf::Vector2f(200, 200));
                nameplate.rectangle.setOrigin(100,100);
                nameplate.rectangle.setRotation(60);
                nameplate.rectangle.setFillColor(sf::Color(255,183,72));
                nameplate.rectangle.setOutlineColor(sf::Color(128,91,36));

                Static borders(&window);
                borders.rectangle.setSize(sf::Vector2f(2000, 2000));
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

                Static headlights(&window);
                headlights.rectangle.setSize(sf::Vector2f(100,100));
                headlights.rectangle.setOrigin(headlights.rectangle.getSize().x/2, headlights.rectangle.getSize().y/2);
                headlights.rectangle.setFillColor(sf::Color(255, 255, 255, 60));
                headlights.rectangle.setOutlineThickness(0);
                headlights.texture.loadFromFile("images/headlights.png");
                headlights.rectangle.setTexture(headlights.pTexture);

                Static youdied(&window);
                youdied.rectangle.setFillColor(sf::Color(255, 255, 255, 150));
                youdied.rectangle.setOutlineThickness(0);
                youdied.texture.loadFromFile("images/youdied.png");
                youdied.rectangle.setTexture(youdied.pTexture);

                Turret turret(&window);
                turret.rectangle.setPosition(1200, 1200);

                Aid aid(&window);
                Battery battery(&window);

                sf::Clock clock;
                float timer = 0, delay = 0.0069;
                sf::View observation;

                observation.setSize(sf::Vector2f(800.f, 450.f));
                youdied.rectangle.setSize(sf::Vector2f(observation.getSize().x, observation.getSize().y/4));

                sf::Font font;//шрифт
                font.loadFromFile("arial.ttf");//передаем нашему шрифту файл шрифта
                sf::Text textV("", font, 20);
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

                std::vector<Bullet*> BulletList;

                std::vector<Aid*> AidList;
                AidList.push_back(&aid);

                std::vector<Battery*> BatteryList;
                BatteryList.push_back(&battery);

                std::vector<Static*> CollisionListStatic;
                CollisionListStatic.push_back(&obstacle);
                CollisionListStatic.push_back(&testobstacle);
                CollisionListStatic.push_back(&borders);
                CollisionListStatic.push_back(&turret);

                std::vector<Dynamic*> CollisionListDynamic;
                CollisionListDynamic.push_back(&player);

                auto it = BulletList.begin();
                int ii = 0;

                while(window.isOpen())
                {
                    float time = clock.getElapsedTime().asSeconds();
                    float time1 = clock.getElapsedTime().asMicroseconds();
                    clock.restart();
                    timer += time;

                    if (time1 > delay) {
                        for(Dynamic *m : CollisionListDynamic)
                        {
                            for(Static *n : CollisionListStatic)
                            {
                                if(CollisionCircleRectangle(*m, *n))
                                {
                                    if(abs(m->v.x) > 0.5*m->vmax)
                                    {
                                        if(m->health/m->healthmax > 0.25*abs((m->v.x/m->vmax)))
                                        {
                                            //m->health -= 0.25*(abs(m->v.x)*m->healthmax)/m->vmax;
                                        }
                                        else if(m->alive) {
                                            death(m);
                                        }
                                    }
                                    ResolveCollisionDynamicObstacle(m, *n);
                                    //m->v.x = 0;
                                }
                            }
                        }
                        for(auto i=AidList.begin(); i!=AidList.end(); i++, ii++) {
                            if(CollisionCircleRectangle(player, *AidList[ii])){
                                player.health += AidList[ii]->hpregen;
                                AidList[ii]->aid.play();
                                if (player.health > player.healthmax)
                                    player.health = player.healthmax;
                                i = AidList.erase(i);
                                ii++;
                            }
                            if (i == AidList.end()) break;
                        }
                        ii = 0;

                        for(auto i=BatteryList.begin(); i!=BatteryList.end(); i++, ii++) {
                            if(CollisionCircleRectangle(player, *BatteryList[ii])){
                                player.energy += BatteryList[ii]->energyregen;
                                BatteryList[ii]->battery.play();
                                if (player.energy > player.energymax)
                                    player.energy = player.energymax;
                                i = BatteryList.erase(i);
                                ii++;
                            }
                            if (i == BatteryList.end()) break;
                        }
                        ii = 0;

                        lightning.rectangle.setFillColor(sf::Color(0,0,0, 100*(-cos(timer*6.28/60)+1)));
                        player.update(time1, timer);
                        TurretUpdate(&turret, player, time1, timer, &fps, &window, &BulletList);
                        for(it=BulletList.begin(); it != BulletList.end(); it++, ii++) {
                            BulletList[ii]->update(time1, timer);
                            if((timer - BulletList[ii]->birthtime) > BulletList[ii]->lifetime){
                                it = BulletList.erase(it);
                                ii++;
                                if (it == BulletList.end()) break;
                            }
                            if(CollisionCircleCircle(*BulletList[ii], player))
                            {
                                if(player.health > BulletList[ii]->damage)
                                    player.health -= BulletList[ii]->damage;
                                else if(player.alive) {
                                    death(&player);
                                }
                                it = BulletList.erase(it);
                                ii++;
                                if (it == BulletList.end()) break;
                            }
                        }
                        ii = 0;
                        health.str(std::string());
                        health << round(player.health*100/player.healthmax);
                        energy.str(std::string());
                        energy << round(player.energy*100/player.energymax);
                        tickrate.str(std::string());
                        tickrate << 1000000/time1;		//делим миллион микросекунд на время одного апдейта
                        //fps.str(std::string());
                        //fps << 1000000/time1;		//делим секунду на время одной прорисовки
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

                        message.rectangle.setPosition(observation.getCenter().x-400+10, observation.getCenter().y+50);
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
                        window.draw(testobstacle);
                        window.draw(nameplate);
                        for(Aid* n : AidList){
                            window.draw(*n);
                        }
                        for(Battery* n : BatteryList){
                            window.draw(*n);
                        }

                        window.draw(turret);

                        for(Bullet* n : BulletList) {
                            window.draw(*n);
                        }

                        window.draw(player);

                        if(player.alive) {
                            window.draw(healthbar);
                            window.draw(healthbarInside);
                            window.draw(energybar);
                            window.draw(energybarInside);
                        }
                        else
                        {
                            youdied.rectangle.setPosition(observation.getCenter().x-(observation.getSize().x/2), observation.getCenter().y-(observation.getSize().y/8));
                            window.draw(youdied);
                        }

                        window.draw(lightning);


                        if(player.headlights)
                        {
                            headlights.rectangle.setRotation(player.rectangle.getRotation()+90);
                            headlights.rectangle.setPosition(player.rectangle.getPosition().x + 1.5*player.rectangle.getSize().x*sin((headlights.rectangle.getRotation()-90)*0.0175), player.rectangle.getPosition().y - 1.5*player.rectangle.getSize().x*cos((headlights.rectangle.getRotation()-90)*0.0175));
                            window.draw(headlights);
                        }

                        playerVelocity.str(std::string());
                        playerVelocity << (player.v.x)/(player.vmax);		//занесли в нее отношение скорости к максимальной скорости
                        textV.setString("V =" + playerVelocity.str());//задаем строку тексту и вызываем сформированную выше строку методом .str()
                        textV.setPosition(observation.getCenter().x - 350, observation.getCenter().y - 200);//задаем позицию текста, отступая от центра камеры
                        textFPS.setString("NeededAngle =" + fps.str());
                        textFPS.setPosition(observation.getCenter().x - 350, observation.getCenter().y - 170);
                        texttickrate.setString("tickrate =" + tickrate.str());
                        texttickrate.setPosition(observation.getCenter().x - 350, observation.getCenter().y - 140);
                        texthealth.setString(health.str() + "%");
                        texthealth.setPosition(healthbar.rectangle.getPosition().x+14, healthbar.rectangle.getPosition().y-2);
                        textenergy.setString(energy.str() + "%");
                        textenergy.setPosition(energybar.rectangle.getPosition().x+14, energybar.rectangle.getPosition().y-2);

                        if(player.alive) {
                            window.draw(texthealth);
                            window.draw(textenergy);
                        }

                        window.draw(textV);//рисую этот текст
                        window.draw(textFPS);
                        window.draw(texttickrate);

                        if(CollisionCircleRectangle(player, nameplate))
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
                            menuin(window2, isMenu, window,player, timer, time1);
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