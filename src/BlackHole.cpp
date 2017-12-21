#include <iostream>

#include "BlackHole.hpp"
#include "Game.hpp"

BlackHole::BlackHole(unsigned x, unsigned y) : Entity(x, y) {

}

BlackHole::~BlackHole() {

}

void BlackHole::draw() const {
//    std::cout << "DRAW BLACKHOLE" << std::endl;

    unsigned pos_x = ENTITY_WIDTH * m_x + Map::OFFSET_X;
    unsigned pos_y = ENTITY_HEIGHT * m_y + Map::OFFSET_Y;

    sf::RectangleShape rectangle(sf::Vector2f(ENTITY_WIDTH, ENTITY_HEIGHT));
    rectangle.move(pos_x, pos_y);
    rectangle.setFillColor(::Color::Green);

    Game::m_main_window.draw(rectangle);
}
