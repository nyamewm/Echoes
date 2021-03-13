#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "menu.h"
#include <SFML/System/Clock.hpp>



int main () {
    sf::RenderWindow window1(sf::VideoMode(1920, 1020), "Menu");
    menu(window1);
    return 0;
}