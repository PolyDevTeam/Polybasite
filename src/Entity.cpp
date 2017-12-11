#include <iostream>

#include <SFML/Graphics/RectangleShape.hpp>

#include "Game.hpp"
#include "Entity.hpp"
#include "Color.hpp"

void Entity::draw() const {
    // TODO : Tempory method
    sf::RectangleShape rectangle(sf::Vector2f(ENTITY_WIDTH, ENTITY_HEIGHT));

    rectangle.setFillColor(::Color::Grey);

    Game::m_main_window.draw(rectangle);
}