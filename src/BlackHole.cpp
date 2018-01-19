#include <iostream>
#include <sstream>

#include "BlackHole.hpp"
#include "Game.hpp"
#include "Util.hpp"

BlackHole::BlackHole() : Entity() {

}

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

std::string BlackHole::serialize() {
    std::ostringstream os;

    os << "BlackHole:" << m_x << ";" << m_y;

    return os.str();
}

void BlackHole::deserialize(std::string serializable) {
    string str = serializable;
    string result = Util::extract(str, ':');

    if(result != "BlackHole") {
        // TODO : Create a good error
        std::cout << result << std::endl;
        std::cout << "Ce n'est pas un objet BlackHole" << std::endl;
        return;
    }

    result = Util::extract(str, ';');
    m_x = atoi(result.c_str());

    result = Util::extract(str, ';');
    m_y = atoi(result.c_str());
}

void BlackHole::interact(Bot *bot, Miner *miner) {
    // TODO : Need a test
    bot->deleteMiner(miner);
    Game::m_map.setEntity(new Basite(miner->getX(), miner->getY(), 0));
}
