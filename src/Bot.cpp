#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Network.hpp>
#include "Bot.hpp"
#include "Color.hpp"
#include "Game.hpp"

Bot::Bot(std::string name, unsigned x, unsigned y) : m_name(name) {
    // Add first miner
    m_miners.push_back(new Miner(x, y));
}

Bot::~Bot() {
    for (unsigned i = 0; i < m_miners.size(); ++i) {
        m_miners[i] = 0;
        delete m_miners[i];
    }
}

void Bot::connection(unsigned short port) {
    sf::UdpSocket socket;
    if (socket.bind(port) != sf::Socket::Done){
        std::cerr << "ERROR : SOCKET" << std::endl;
    }

    std::string data = "Bonjour";
    if (socket.send(data.data(), data.size(), "127.0.0.1", port) != sf::Socket::Done){
        std::cerr << "ERROR : SENDING DATA" << std::endl;
    }
}
