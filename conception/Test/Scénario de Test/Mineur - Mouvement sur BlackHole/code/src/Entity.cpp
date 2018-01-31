#include <SFML/Graphics/RectangleShape.hpp>

#include "Game.hpp"
#include "Entity.hpp"
#include "Color.hpp"

Entity::Entity(unsigned x, unsigned y) : m_x(x), m_y(y) {

}

Entity::~Entity() {

}

void Entity::draw() const {
    sf::RectangleShape rectangle(sf::Vector2f(ENTITY_WIDTH, ENTITY_HEIGHT));

    rectangle.setFillColor(::Color::Grey);

    Game::m_main_window.draw(rectangle);
}

unsigned Entity::getX() const {
    return m_x;
}

unsigned Entity::getY() const {
    return m_y;
}
