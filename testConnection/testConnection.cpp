#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Network.hpp>
#include <vector>


int main(int argc, char* argv[]) {


    unsigned short port = 7777;
    sf::IpAddress sender;

    std::cout << "en attente des bots" << std::endl;

    sf::UdpSocket socket;
    // lie la socket à un port
    if (socket.bind(port) != sf::Socket::Done) {
        std::cerr << "ERREUR SOCKET" << '\n';
    }


    char data[100];
    std::size_t received;

    if (socket.receive(data, 100, received, sender, port) != sf::Socket::Done) {
        std::cerr << "ERREUR RECEIVE" << '\n';
    }

    std::cout << "Received " << received << " bytes from " << sender << " on port " << port << std::endl;

    std::cout << "Message : " << data << std::endl;

}
