#include <iostream>
#include <sstream>

#include <SFML/Graphics/RectangleShape.hpp>

#include "Miner.hpp"
#include "Game.hpp"
#include "Util.hpp"

Miner::Miner(unsigned x, unsigned y) : Entity(x, y) {
    Game::m_map.setEntity(this);
}

Miner::~Miner() {

}

void Miner::draw() const {
//    std::cout << "DRAW MINER" << std::endl;
    unsigned pos_x = ENTITY_WIDTH * m_x + Map::OFFSET_X;
    unsigned pos_y = ENTITY_HEIGHT * m_y + Map::OFFSET_Y;

    sf::RectangleShape rectangle(sf::Vector2f(ENTITY_WIDTH, ENTITY_HEIGHT));
    rectangle.move(pos_x, pos_y);

    rectangle.setFillColor(::Color::Red);

    Game::m_main_window.draw(rectangle);
}

std::string Miner::serialize() {
    std::ostringstream os;

    std::cout << "MINER" << std::endl;
    os << "Miner:" << m_x << ";" << m_y;

    return os.str();
}

void Miner::deserialize(std::string serializable) {
    string str = serializable;
    string result = Util::extract(str, ':');

    if(result != "Miner") {
        std::cout << result << std::endl;
        std::cout << "Ce n'est pas un objet Miner" << std::endl;
        return;
    }

    result = Util::extract(str, ';');
    m_x = atoi(result.c_str());

    result = Util::extract(str, ';');
    m_y = atoi(result.c_str());
}