#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Miner.hpp"
#include "Game.hpp"

Miner::Miner(unsigned x, unsigned y, unsigned power, sf::Color c) : Entity(x, y), m_power(power), m_color(c) {
    Game::m_map.setEntity(this);
    std::cout << "- Miner en " << m_x << " " << m_y << std::endl;

}

Miner::~Miner() {

}

void Miner::draw() const {

    unsigned pos_x = ENTITY_WIDTH * m_x + Map::OFFSET_X;
    unsigned pos_y = ENTITY_HEIGHT * m_y + Map::OFFSET_Y;

    sf::RectangleShape rectangle(sf::Vector2f(ENTITY_WIDTH, ENTITY_HEIGHT));
    rectangle.move(pos_x, pos_y);

    unsigned power = MAX_POWER + (MAX_POWER - m_power);

    sf::RectangleShape foreground(sf::Vector2f(ENTITY_WIDTH - power, ENTITY_HEIGHT - power));
    foreground.setOrigin(sf::Vector2f((ENTITY_WIDTH - power) / 2, (ENTITY_HEIGHT - power) / 2));
    foreground.move(pos_x + MAX_POWER, pos_y + MAX_POWER);

    rectangle.setFillColor(m_color);

    Game::m_main_window.draw(rectangle);
    Game::m_main_window.draw(foreground);

}

unsigned int Miner::getPower() const {
    return m_power;
}

void Miner::setPower(unsigned int power){
    m_power = power;
}
