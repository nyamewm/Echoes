#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "menu.h"
#include "game.h"
#include "map.h"


int main () {
    sf::RenderWindow window1(sf::VideoMode(740, 500), "Menu");
    menu(window1);
    return 0;
}