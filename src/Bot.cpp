#include <iostream>

#include <SFML/Graphics/RectangleShape.hpp>

#include "Bot.hpp"
#include "Color.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "Util.hpp"

void programBot(std::string directory, int port) {
    // std::to_string introduced in C++11
    std::string exePath = "./bot/" + directory + "/" + directory + ".exe "+ std::to_string(port) + " 1"; // TODO : Maybe remove id ?
    system(exePath.c_str()); // TODO : Maybe an other function will be better for portability
}

Bot::Bot(std::string directory, unsigned x, unsigned y) {
    // Request Bot name
    m_socket = new plb::Socket(0);

    // Launch the bot program
    m_instance = std::thread(&programBot, directory, m_socket->getPort());

    // TODO : Sleep bot program thread when I got the good information ?
    // TODO : Bot has 3sec to response when it's his turn else he sleep

    // The first exchange is name;port
    std::string receive = m_socket->receive();
    m_name = Util::extract(receive, ';');

    LOG << "[Polybasite] Discover bot : " << m_name << '\n';

    // Get listen port
    m_port = atoi(receive.c_str());
    std::cout << "PORT TO LISTEN BY MAIN THREAD = " << m_port << std::endl;

    // Add first miner
    Miner* miner = new Miner(x, y);
    m_miners.push_back(miner);
    Game::m_map.setEntity(miner);

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
}