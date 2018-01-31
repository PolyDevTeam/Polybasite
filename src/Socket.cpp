#include <iostream>

#include "Socket.hpp"

using namespace plb;

Socket::Socket(int port) : m_port(port), m_socket() {
    // Default constructor is prohibited by SFML
    if(port == 0) {
        m_port = rand() % (65535 - 49152) + 49152; // Free port range
    }

    if(m_socket.bind(m_port) != sf::Socket::Done) {
        // TODO : Have a good error method for log and try catch it
        std::cerr << "[POLYBASITE] Error" << std::endl;
        exit(-1);
    }
}

int Socket::getPort() const {
    return m_port;
}

std::string Socket::receive() {
    std::size_t received;

    char data[sf::UdpSocket::MaxDatagramSize];

    // socket UDP:
    sf::IpAddress sender;
    unsigned short port;
    if (m_socket.receive(data, sf::UdpSocket::MaxDatagramSize, received, sender, port) != sf::Socket::Done) {
        // TODO : Create an error
    }

    return std::string(data);
}

std::string Socket::receive(int timeout) {
    sf::SocketSelector selector;
    selector.add(m_socket);

    if(selector.wait(sf::seconds(timeout))) {
        std::size_t received;

        char data[sf::UdpSocket::MaxDatagramSize];

        // socket UDP:
        sf::IpAddress sender;
        unsigned short port;
        if (m_socket.receive(data, sf::UdpSocket::MaxDatagramSize, received, sender, port) != sf::Socket::Done) {
            // TODO : Create an error
        }

        return data;
    }
    else
        return "TIMEOUT"; // TODO : Create an exception Error
}

void Socket::send(std::string ipAddress, int port, std::string msg) {
    sf::IpAddress recipient = ipAddress;

    if (m_socket.send(msg.c_str(), msg.size(), recipient, port) != sf::Socket::Done) {
        // TODO: Create an error
        std::cerr << "Erreur dans l'envoie du message" << std::endl;
    }
}

void Socket::send(std::string ipAddress, int port, Serializable *serializable) {
    send(ipAddress, port, serializable->serialize());
}
