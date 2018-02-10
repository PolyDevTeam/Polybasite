#include <iostream>
#include <iterator>
#include <set>

#include <SFML/Graphics/RectangleShape.hpp>

#include "Bot.hpp"
#include "Color.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "Util.hpp"
#include "Move.hpp"
#include "Error.hpp"

void programBot(std::string directory, int port, unsigned id) {
    // std::to_string introduced in C++11
    std::string exePath = "./bot/" + directory + "/" + directory + ".exe "+ std::to_string(port) + " " + std::to_string(id);

    if(system(exePath.c_str()) == -1) {  // TODO : Maybe an other function will be better for portability
        throw Error();
    }
}

Bot::Bot(std::string directory, unsigned x, unsigned y, unsigned id) {
    m_owner = id;

    // Request Bot name
    m_socket = new plb::Socket(0);

    // Launch the bot program
    m_instance = std::thread(&programBot, directory, m_socket->getPort(), id);

    // TODO : Bot has 3sec to response when it's his turn else he sleep
    // The first exchange is name;port
    std::string receive = m_socket->receive();

    m_name = Util::extract(receive, ';');

    LOG << "[Polybasite] Discover bot : " << m_name << '\n';

    // Get listen port
    m_port = atoi(receive.c_str());
    std::cout << "PORT TO LISTEN BY MAIN THREAD = " << m_port << std::endl;

    // Add first miner
    addMiner(x, y, 0);

    // Send Map to the bot
    LOG << "[Polybasite] Send map to : " << m_name << '\n';
    m_socket->send("127.0.0.1", m_port, &Game::m_map);
}

Bot::~Bot() {
    for (unsigned i = 0; i < m_miners.size(); ++i) {
        m_miners[i] = 0;
        delete m_miners[i];
    }

    m_instance.detach();

    delete m_socket;
    m_socket = nullptr;
}

string Bot::getName() const {
    return m_name;
}

sf::Color Bot::getColor() const {
    return m_color;
}

void Bot::setColor(sf::Color color) {
    m_color = color;

    for(Miner* miner : m_miners)
        miner->setColor(m_color);
}

void Bot::turn() {
    // Add one power by miner
    for (Miner *miner : m_miners) {
        if (miner->getPower() < Miner::MAX_POWER - 1) {
            miner->setPower(miner->getPower() + 1);
        }
    }

    // Send map to the bot
    m_socket->send("127.0.0.1", m_port, &Game::m_map);

    std::string moveString = m_socket->receive();

    std::set<Move> moves;

    while(moveString.size() > 0) {
        Move move;
        move.deserialize(moveString);
        moves.insert(move);
    }

    for(Move move : moves) {
        move.move(m_miners);
    }
}

void Bot::addMiner(unsigned x, unsigned y, unsigned power) {
    Miner* miner = new Miner(m_owner, x, y);
    miner->setColor(m_color);
    miner->setPower(power);
    Game::m_map.setEntity(miner);
    m_miners.push_back(miner);
}

void Bot::deleteMiner(Miner *m) {
    for(std::vector<Miner*>::iterator it = m_miners.begin(); it < m_miners.end(); ++it) {
        if(*it == m) {
            m_miners.erase(std::remove(m_miners.begin(), m_miners.end(), m), m_miners.end());
        }
    }
}

unsigned Bot::getOwner() const {
    return m_owner;
}

unsigned Bot::getMinerNumber() const {
    return m_miners.size();
}

unsigned Bot::getPower() const {
    unsigned power = 0;

    for(Miner* miner: m_miners) {
        power += miner->getPower();
    }

    return power;
}

void Bot::stopBot() {
    m_socket->send("127.0.0.1", m_port, "END");
}