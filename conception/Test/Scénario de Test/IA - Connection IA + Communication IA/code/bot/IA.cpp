#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

int main(int argc, char* argv[]) {


    unsigned short port_a = 7777;
    unsigned short port_b;
    sf::IpAddress sender;

    std::cout << "- en attente " << std::endl;

    sf::UdpSocket socket;
    // lie la socket à un port
    if (socket.bind(port_a) != sf::Socket::Done) {
        std::cerr << "ERREUR SOCKET" << '\n';
    }


    char data[100];
    std::size_t received;

    if (socket.receive(data, 100, received, sender, port_b) != sf::Socket::Done) {
        std::cerr << "ERREUR RECEIVE" << '\n';
    }

    std::cout << "Received " << received << " bytes from " << sender << " on port " << port_b << std::endl;

    std::cout << "Message : " << data << std::endl;

    std::this_thread::sleep_for (std::chrono::seconds(1));

    char data2[100] = "- Test Communication IA -----> JEU ";

    if (socket.send(data2, 100, sender, port_b) != sf::Socket::Done) {
        std::cerr << "ERREUR EMISSION" << '\n';
    }

}
