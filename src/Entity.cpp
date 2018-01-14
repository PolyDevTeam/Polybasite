#include <sstream>

#include <SFML/Graphics/RectangleShape.hpp>

#include "Game.hpp"
#include "Entity.hpp"
#include "Color.hpp"
#include "Util.hpp"

Entity::Entity() : m_x(0), m_y(0) {

}

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

std::string Entity::serialize() {
    std::ostringstream os;

    os << "Entity:" << m_x << ";" << m_y;

    return os.str();
}

void Entity::deserialize(std::string serializable) {
    string str = serializable;
    string result = Util::extract(str, ':');

    if(result != "Entity") {
        std::cout << result << std::endl;
        std::cout << "Ce n'est pas un objet Entity" << std::endl;
        return;
    }

    result = Util::extract(str, ';');
    m_x = atoi(result.c_str());

    result = Util::extract(str, ';');
    m_y = atoi(result.c_str());
}