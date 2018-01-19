#include <iostream>
#include <sstream>

#include <SFML/Graphics/RectangleShape.hpp>

#include "Game.hpp"
#include "Basite.hpp"
#include "Color.hpp"
#include "Util.hpp"

Basite::Basite() : Entity(), m_power(0) {

}

Basite::Basite(unsigned x, unsigned y, unsigned power) : Entity(x, y), m_power(power) {

}

Basite::~Basite() {

}

void Basite::draw() const {
    unsigned pos_x = ENTITY_WIDTH * m_x + Map::OFFSET_X;
    unsigned pos_y = ENTITY_HEIGHT * m_y + Map::OFFSET_Y;

    sf::RectangleShape rectangle(sf::Vector2f(ENTITY_WIDTH, ENTITY_HEIGHT));
    rectangle.move(pos_x, pos_y);
    rectangle.setFillColor(::Color::Grey);

    unsigned power = MAX_POWER + (MAX_POWER - m_power);

    sf::RectangleShape foreground(sf::Vector2f(ENTITY_WIDTH - power, ENTITY_HEIGHT - power));
    foreground.setOrigin(sf::Vector2f((ENTITY_WIDTH - power) / 2, (ENTITY_HEIGHT - power) / 2));
    foreground.move(pos_x + MAX_POWER, pos_y + MAX_POWER);

    foreground.setFillColor(::Color::White);

    Game::m_main_window.draw(rectangle);
    Game::m_main_window.draw(foreground);
}


std::string Basite::serialize() {
    std::ostringstream os;

    os << "Basite:" << m_x << ";" << m_y;

    return os.str();
}

void Basite::deserialize(std::string serializable) {
    string str = serializable;
    string result = Util::extract(str, ':');

    if(result != "Basite") {
        std::cout << result << std::endl;
        std::cout << "Ce n'est pas un objet Basite" << std::endl;
        exit(-1);
    }

    result = Util::extract(str, ';');
    m_x = atoi(result.c_str());

    result = Util::extract(str, ';');
    m_y = atoi(result.c_str());
}