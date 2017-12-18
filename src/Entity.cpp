#include <SFML/Graphics/RectangleShape.hpp>

#include "Game.hpp"
#include "Entity.hpp"
#include "Color.hpp"

Entity::Entity(unsigned x, unsigned y) : m_x(x), m_y(y) {

}

Entity::~Entity() {

}

void Entity::draw() const {
//     TODO : Tempory method
    std::cout << "ENTITY DRAW" << std::endl;

    sf::RectangleShape rectangle(sf::Vector2f(ENTITY_WIDTH, ENTITY_HEIGHT));

    rectangle.setFillColor(::Color::Grey);

    Game::m_main_window.draw(rectangle);
}