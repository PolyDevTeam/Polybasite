#include <iostream>
#include <stdlib.h>

#include "Color.hpp"

const sf::Color plb::Color::Grey = sf::Color(136, 136, 136, 150);
std::vector<sf::Color> plb::Color::colorAlreadyPicked;

bool plb::Color::contain(sf::Color c) {
    for(sf::Color color : colorAlreadyPicked) {
        if(color == c)
            return true;
    }

    return false;
}

sf::Color plb::Color::selectRandomSingle() {
    unsigned random = rand() % (MAX_RAND_COLOR);

    if(colorAlreadyPicked.size() == MAX_RAND_COLOR)
        return sf::Color::Black;

    switch(random) {
        case 1: // Red
            if(!contain(sf::Color::Red)) {
                colorAlreadyPicked.push_back(sf::Color::Red);
                return sf::Color::Red;
            }
            else {
                return selectRandomSingle();
            }
        case 2: // Blue
            if(!contain(sf::Color::Blue)) {
                colorAlreadyPicked.push_back(sf::Color::Blue);
                return sf::Color::Blue;
            }
            else {
                return selectRandomSingle();
            }
        case 3: // Yellow
            if(!contain(sf::Color::Yellow)) {
                colorAlreadyPicked.push_back(sf::Color::Yellow);
                return sf::Color::Yellow;
            }
            else {
                return selectRandomSingle();
            }
        case 4: // Magenta
            if(!contain(sf::Color::Magenta)) {
                colorAlreadyPicked.push_back(sf::Color::Magenta);
                return sf::Color::Magenta;
            }
            else {
                return selectRandomSingle();
            }
        case 5: // Blue
            if(!contain(sf::Color(34, 187, 234))) {
                colorAlreadyPicked.push_back(sf::Color(34, 187, 234));
                return sf::Color(34, 187, 234);
            }
            else {
                return selectRandomSingle();
            }
        case 6: // Brown
            if(!contain(sf::Color(153, 102, 51))) {
                colorAlreadyPicked.push_back(sf::Color(153, 102, 51));
                return sf::Color(153, 102, 51);
            }
            else {
                return selectRandomSingle();
            }
        case 7: // Orange
            if(!contain(sf::Color(255, 153, 0))) {
                colorAlreadyPicked.push_back(sf::Color(255, 153, 0));
                return sf::Color(255, 153, 0);
            }
            else {
                return selectRandomSingle();
            }
        case 0:
        case 8: // Purple
            if(!contain(sf::Color(204, 51, 255))) {
                colorAlreadyPicked.push_back(sf::Color(204, 51, 255));
                return sf::Color(204, 51, 255);
            }
            else {
                return selectRandomSingle();
            }
        default:
            return sf::Color::Black;
    }

    return sf::Color::Black;
}
