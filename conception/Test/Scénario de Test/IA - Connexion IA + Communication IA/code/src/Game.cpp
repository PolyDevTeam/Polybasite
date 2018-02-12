#include <iostream>
#include <vector>

#include "Game.hpp"


GameState Game::m_state = STATE_UNINITIALISED;

void Game::start(int argc, char *argv[]) {
    if (Game::m_state != STATE_UNINITIALISED)
        return;

    srand(time(NULL)); // Rand initialisation
    Game::m_state = STATE_PLAY;

    sf::UdpSocket socket;

    unsigned short port_a = 8888;
    unsigned short port_b = 7777;

    // lie la socket à un port
    if (socket.bind(port_a) != sf::Socket::Done){
        std::cerr << "ERREUR SOCKET" << '\n';
    }

    char data[100] = "- Test Communication JEU -----> IA ";
    // socket UDP:
    sf::IpAddress recipient = "127.0.0.1";
    if (socket.send(data, 100, recipient, port_b) != sf::Socket::Done) {
        std::cerr << "ERREUR EMISSION" << '\n';
    }

    std::this_thread::sleep_for (std::chrono::seconds(1));

    char data2[100];
    std::size_t received;
    sf::IpAddress sender;

    if (socket.receive(data2, 100, received, sender, port_a) != sf::Socket::Done) {
        std::cerr << "ERREUR RECEIVE" << '\n';
    }

    std::cout << "Received " << received << " bytes from " << sender << " on port " << port_a << std::endl;

    std::cout << "Message : " << data2 << std::endl;

    Game::quit();
}

void Game::quit() {
    if(Game::m_state != STATE_QUIT) {
        Game::m_state = STATE_QUIT;

    }
}
