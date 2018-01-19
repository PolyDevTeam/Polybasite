#include <iostream>
#include <sstream>

#include <SFML/Graphics/RectangleShape.hpp>

#include "Miner.hpp"
#include "Game.hpp"
#include "Util.hpp"

Miner::Miner(unsigned x, unsigned y) : Entity(x, y), m_power(0) {
    Game::m_map.setEntity(this);
}

Miner::~Miner() {

}

void Miner::draw() const {
    unsigned pos_x = ENTITY_WIDTH * m_x + Map::OFFSET_X;
    unsigned pos_y = ENTITY_HEIGHT * m_y + Map::OFFSET_Y;

    sf::RectangleShape rectangle(sf::Vector2f(ENTITY_WIDTH, ENTITY_HEIGHT));
    rectangle.move(pos_x, pos_y);

    rectangle.setFillColor(::Color::Red);

    unsigned power = MAX_POWER + (MAX_POWER - m_power);

    sf::RectangleShape foreground(sf::Vector2f(ENTITY_WIDTH - power, ENTITY_HEIGHT - power));
    foreground.setOrigin(sf::Vector2f((ENTITY_WIDTH - power) / 2, (ENTITY_HEIGHT - power) / 2));
    foreground.move(pos_x + MAX_POWER, pos_y + MAX_POWER);

    foreground.setFillColor(::Color::White);

    Game::m_main_window.draw(rectangle);
    Game::m_main_window.draw(foreground);
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

unsigned Miner::getPower() const {
    return m_power;
}

void Miner::setPower(unsigned power) {
    m_power = power % Miner::MAX_POWER;
}

bool Miner::operator==(const Miner &m) {
    return m_x == m.m_x &&
           m_y == m.m_y &&
           m_power == m.m_power;
}

//void Miner::interact(Bot* bot, Miner *miner) {
//
//}