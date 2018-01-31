#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Miner.hpp"
#include "Game.hpp"

Miner::Miner(unsigned x, unsigned y) : Entity(x, y) {
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

    rectangle.setFillColor(::Color::Red);

    Game::m_main_window.draw(rectangle);
}
