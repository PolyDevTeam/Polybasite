#include <iostream>
#include <sstream>

#include <SFML/Graphics/RectangleShape.hpp>

#include "Miner.hpp"
#include "Game.hpp"
#include "Util.hpp"
#include "Log.hpp"
#include "Basite.hpp"

Miner::Miner() : Entity() {

}

Miner::Miner(unsigned owner, unsigned x, unsigned y) : m_owner(owner), Entity(x, y), m_power(0) {
    Game::m_map.setEntity(this);
}

Miner::~Miner() {

}

void Miner::draw() const {
    unsigned pos_x = ENTITY_WIDTH * m_x + Map::OFFSET_X;
    unsigned pos_y = ENTITY_HEIGHT * m_y + Map::OFFSET_Y;

    sf::RectangleShape rectangle(sf::Vector2f(ENTITY_WIDTH, ENTITY_HEIGHT));
    rectangle.move(pos_x, pos_y);

    rectangle.setFillColor(m_color);

    unsigned power = MAX_POWER + (MAX_POWER - m_power);

    sf::RectangleShape foreground(sf::Vector2f(ENTITY_WIDTH - power, ENTITY_HEIGHT - power));
    foreground.setOrigin(sf::Vector2f((ENTITY_WIDTH - power) / 2, (ENTITY_HEIGHT - power) / 2));
    foreground.move(pos_x + MAX_POWER, pos_y + MAX_POWER);

    foreground.setFillColor(plb::Color::White);

    Game::m_main_window.draw(rectangle);
    Game::m_main_window.draw(foreground);
}

std::string Miner::serialize() {
    std::ostringstream os;

    os << "Miner:" << m_x << ";" << m_y << ";" << m_power << ";" << m_owner;

    return os.str();
}

void Miner::deserialize(std::string &serializable) {
    string result = Util::extract(serializable, ':');

    if(result != "Miner") {
        std::cout << result << std::endl;
        std::cout << "Ce n'est pas un objet Miner" << std::endl;
        return;
    }

    result = Util::extract(serializable, ';');
    m_x = atoi(result.c_str());

    result = Util::extract(serializable, ';');
    m_y = atoi(result.c_str());

    result = Util::extract(serializable, ';');
    m_power = atoi(result.c_str());

    result = Util::extract(serializable, ';');
    m_owner = atoi(result.c_str());
}

unsigned Miner::getPower() const {
    return m_power;
}

void Miner::setPower(unsigned power) {
    m_power = power % Miner::MAX_POWER;
}

void Miner::setColor(sf::Color color) {
    m_color = color;
}

bool Miner::operator==(const Miner &m) {
    return m_x == m.m_x &&
           m_y == m.m_y &&
           m_power == m.m_power &&
           m_owner == m.m_owner;
}

unsigned Miner::getOwner() const {
    return m_owner;
}

void Miner::interact(Miner *miner) {
    std::cout << "INTERACT MINER" << std::endl;

    Bot* bot = Game::m_bots[getOwner()];
    Bot* target = Game::m_bots[miner->getOwner()];

    if(this->getOwner() != miner->getOwner()) {
        if(getPower() == miner->getPower()) {
            Game::m_map.setEntity(new Basite(m_x, m_y, 0));
            Game::m_map.setEntity(new Basite(miner->getX(), miner->getY(), 0));
            bot->deleteMiner(this);
            target->deleteMiner(miner);
        }
        else if(getPower() > miner->getPower()) {
            m_power = 0;
            bot->addMiner(miner->getX(), miner->getY(), m_power - miner->getOwner());
            target->deleteMiner(miner);
        }
        else if(getPower() < miner->getPower()) {
            miner->setPower(0);
            bot->addMiner(m_x, m_y, miner->getPower() - m_power);
            bot->deleteMiner(this);
        }
    }
    else {
        // Same owner
        unsigned remaining = (MAX_POWER - 1) - miner->getPower();
        if(remaining > 0) {
            if(m_power >= remaining) {
                miner->setPower(miner->getPower() + remaining);
                m_power -= remaining;
            }
            else {
                miner->setPower(miner->getPower() + m_power);
                m_power = 0;
            }
        }
    }
}