#include <iostream>
#include <sstream>

#include "BlackHole.hpp"
#include "Game.hpp"
#include "Util.hpp"

unsigned BlackHole::m_rotation = 0;
sf::Texture BlackHole::m_texture;

BlackHole::BlackHole() : Entity() {

}

BlackHole::BlackHole(unsigned x, unsigned y) : Entity(x, y) {

}

BlackHole::~BlackHole() {

}

void BlackHole::draw() const {
    unsigned pos_x = ENTITY_WIDTH * m_x + Map::OFFSET_X + 10;
    unsigned pos_y = ENTITY_HEIGHT * m_y + Map::OFFSET_Y + 10;

    sf::Sprite sprite;
    sprite.setTexture(m_texture);
    sprite.setScale(sf::Vector2f(0.15f, 0.15f));
    sprite.setOrigin(sf::Vector2f(70, 70));
    sprite.move(pos_x, pos_y);
    sprite.rotate(m_rotation);

    Game::m_main_window.draw(sprite);
}

std::string BlackHole::serialize() {
    std::ostringstream os;

    os << "BlackHole:" << m_x << ";" << m_y;

    return os.str();
}

void BlackHole::deserialize(std::string &serializable) {
    string result = Util::extract(serializable, ':');

    if(result != "BlackHole") {
        // TODO : Create a good error
        std::cout << result << std::endl;
        std::cout << "Ce n'est pas un objet BlackHole" << std::endl;
        return;
    }

    result = Util::extract(serializable, ';');
    m_x = atoi(result.c_str());

    result = Util::extract(serializable, ';');
    m_y = atoi(result.c_str());
}

void BlackHole::interact(Miner *miner) {
    Bot* bot = Game::m_bots[miner->getOwner()];
    bot->deleteMiner(miner);
    Game::m_map.setEntity(new Basite(miner->getX(), miner->getY(), 0));
}
