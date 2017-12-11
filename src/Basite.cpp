#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Game.hpp"
#include "Basite.hpp"
#include "Color.hpp"

Basite::~Basite() {

}

void Basite::draw() const {
    std::cout << "DRAW BASITE" << std::endl;

    sf::RectangleShape rectangle(sf::Vector2f(ENTITY_WIDTH, ENTITY_HEIGHT));

    rectangle.setFillColor(::Color::Grey);

    Game::m_main_window.draw(rectangle);
}
