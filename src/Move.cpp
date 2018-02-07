#include <sstream>

#include "Move.hpp"
#include "Game.hpp"
#include "Util.hpp"
#include "Log.hpp"

Move::Move(unsigned minerId, DIRECTIONS directions) : m_directions(directions), m_minerId(minerId) {

}

Move::Move() : Move(0, STILL) {

}

Move::~Move() {

}

std::string Move::serialize() {
    std::ostringstream os;

    os << "Move:" << m_minerId << ";" << m_directions;

    return os.str();
}

void Move::deserialize(std::string &serializable) {
    string result = Util::extract(serializable, ':');

    if(result != "Move") {
        std::cout << result << std::endl;
        std::cout << "Ce n'est pas un objet Move" << std::endl;
        exit(1);
        return;
    }

    result = Util::extract(serializable, ';');
    m_minerId = atoi(result.c_str());

    result = Util::extract(serializable, ';');
    m_directions = (DIRECTIONS) atoi(result.c_str());
}

void Move::move(std::vector<Miner*> &miners) const {
    Miner* miner = miners[m_minerId];
    std::string botName = Game::m_bots[miner->getOwner()]->getName();

    int offset_x = miner->getX();
    int offset_y = miner->getY();

    LOG << "[" << botName << " (" << miner->getOwner() << ")" << "] ";
    switch(m_directions) {
        case NORTH:
            LOG << "Move NORTH" << '\n';
            offset_y = (offset_y - 1 + Game::m_map.getHeight())%Game::m_map.getHeight();
            break;
        case EAST:
            LOG << "Move EAST" << '\n';
            offset_x = (offset_x + 1 + Game::m_map.getWidth())%Game::m_map.getWidth();
            break;
        case SOUTH:
            LOG << "Move SOUTH" << '\n';
            offset_y = (offset_y + 1 + Game::m_map.getHeight())%Game::m_map.getHeight();
            break;
        case WEST:
            LOG << "Move WEST" << '\n';
            offset_x = (offset_x - 1 + Game::m_map.getWidth())%Game::m_map.getWidth();
            break;
        case STILL:
            LOG << "Move STILL" << '\n';
            break;
        default:
            // TODO : Create error
            LOG << "Unkown movement" << '\n';
            exit(-1);
            break;
    }

    if(m_directions != STILL) {
        Entity* entity = Game::m_map[offset_x][offset_y];
        entity->interact(miners[m_minerId]);
    }
}

bool Move::operator<(const Move &move) const {
    return m_minerId < move.m_minerId;
}

Move& Move::operator=(const Move& move) {
    m_minerId = move.m_minerId;
    m_directions = move.m_directions;
    return *this;
}