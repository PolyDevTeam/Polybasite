#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Game.hpp"
#include "Basite.hpp"
#include "Color.hpp"

Basite::Basite(unsigned x, unsigned y, unsigned power) : Entity(x, y), m_power(power) {
    std::cout << "- Basite en " << m_x << " " << m_y << std::endl;
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

unsigned int Basite::getPower() const {
    return m_power;
}

void Basite::setPower(unsigned int power){
    m_power = power;
}
