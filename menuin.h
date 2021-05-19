#include <sstream>
#include <string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>
#include<vector>

using namespace rapidjson;
std::string GetElementValue(const Value& val)
{
    if (val.GetType() == Type::kNumberType)
        return std::to_string(val.GetDouble());
}






void load(std::string file_name, Player &player, float &timer){
    std::vector<float> datb;
    std::ifstream ifs("save.json");
    IStreamWrapper isw(ifs);
    Document documentFromFile;

    documentFromFile.ParseStream(isw);

    for (Value::ConstMemberIterator iter = documentFromFile.MemberBegin(); iter != documentFromFile.MemberEnd(); ++iter) {
         datb.push_back(std::stof(GetElementValue(iter->value)));
    }
    player.rectangle.setPosition(datb[0], datb[1]);
    player.health = (datb[2]);
    player.energy = (datb[3]);
    player.headlights = (datb[4]);
    timer = (datb[5]);
}


void save(Player player, float &timer){
    char cbuf[1024];
    rapidjson::MemoryPoolAllocator<> allocator (cbuf, sizeof cbuf);
    rapidjson::Document meta (&allocator, 256);
    meta.SetObject();
    meta.AddMember ("x", player.rectangle.getPosition().x, allocator);
    meta.AddMember ("y", player.rectangle.getPosition().y, allocator);
    meta.AddMember ("hp", player.health, allocator);
    meta.AddMember ("energy", player.energy, allocator);
    meta.AddMember ("energy", player.headlights, allocator);
    meta.AddMember ("timer", timer, allocator);


    typedef rapidjson::GenericStringBuffer<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>> StringBuffer;
    StringBuffer buf (&allocator);
    Writer<StringBuffer> writer(buf);
    meta.Accept (writer);
    std::string json (buf.GetString(), buf.GetSize());

    std::ofstream of ("save.json");
    of << json;
    if (!of.good()) throw std::runtime_error ("Can't write the JSON string to the file!");

}



void menuin(sf::RenderWindow & window2, bool & isMenu, sf::RenderWindow & window1,Player &player, float &timer, float &time1) {




    std::vector <int> m1 {150, 250};
    std::vector <int> m2 {150, 300};
    std::vector <int> m4 {150, 350};
    std::vector <int> m3 {150, 400};

    sf::Texture menuTexture1, menuTexture2, menuTexture3,menuTexture4, aboutTexture, menuBackground;
    menuTexture1.loadFromFile("images/444.png");
    menuTexture2.loadFromFile("images/222.png");
    menuTexture3.loadFromFile("images/333.png");
    menuTexture4.loadFromFile("images/555.png");

    sf::Font font;//шрифт
    font.loadFromFile("arial.ttf");//передаем нашему шрифту файл шрифта
    sf::Text text1("Resume", font, 30);
    sf::Text text2("Load", font, 30);
    sf::Text text3("Quit", font, 30);
    sf::Text text4("Save", font, 30);

    menuBackground.loadFromFile("images/menu.jpg");
    sf::Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3),menu4(menuTexture4), menuBg(menuBackground);
    bool isMenuin = 1;
    int menuNum = 0;
    text1.setPosition(m1[0], m1[1]);
    text2.setPosition(m2[0], m2[1]);
    text3.setPosition(m3[0], m3[1]);
    text4.setPosition(m4[0], m4[1]);
    menuBg.setPosition(0, 0);






    while (isMenuin) {

        text1.setColor(sf::Color::White);
        text2.setColor(sf::Color::White);
        text3.setColor(sf::Color::White);
        text4.setColor(sf::Color::White);
        menuNum = 0;
        window2.clear(sf::Color(129, 181, 221));

        if (sf::IntRect(m1[0], m1[1], 300, 50).contains(sf::Mouse::getPosition(window2))) {
            text1.setColor(sf::Color::Yellow);
            menuNum = 1;
        };
        if (sf::IntRect(m2[0], m2[1], 300, 50).contains(sf::Mouse::getPosition(window2))) {
            text2.setColor(sf::Color::Yellow);
            menuNum = 2;
        };
        if (sf::IntRect(m3[0], m3[1], 300, 50).contains(sf::Mouse::getPosition(window2))) {
            text3.setColor(sf::Color::Yellow);
            menuNum = 3;
        };
        if (sf::IntRect(m4[0], m4[1], 300, 50).contains(sf::Mouse::getPosition(window2))) {
            text4.setColor(sf::Color::Yellow);
            menuNum = 4;
        };

        sf::Event event;
        while (window2.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                isMenuin = false;
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (menuNum == 1) isMenuin = false;
            if (menuNum == 3) {
                isMenuin = false;
                window1.close();
                isMenu = false;
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { //кнопка сохранений
            if (menuNum == 1) isMenuin = false;
            if (menuNum == 4) {
                save(player, timer);
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { //кнопка загрузки
            if (menuNum == 1) isMenuin = false;
            if (menuNum == 2) {
                load("save", player, timer);
            }
        }
        window2.clear();

        window2.draw(menuBg);
        window2.draw(text1);
        window2.draw(text2);
        window2.draw(text3);
        window2.draw(text4);


        window2.display();
    }
}

