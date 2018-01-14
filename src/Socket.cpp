#include <iostream>

#include "Socket.hpp"

using namespace plb;

Socket::Socket(int port) : m_port(port), m_socket() {
    // Default constructor is prohibited by SFML
    if(port == 0) {
        m_port = rand() % (65535 - 49152) + 49152;
    }

    if(m_socket.bind(m_port) != sf::Socket::Done) {
        // TODO : Have a good error method for log and try catch it
        std::cout << "Error" << std::endl;
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
        // erreur...
    }

    std::cout << "Received " << received << " bytes from " << sender << " on port " << port << std::endl;
    std::cout << "Data = " << data << std::endl;

    return std::string(data);
}

//void receive(int timeout) {
//
//}

void Socket::send(std::string ipAddress, int port, std::string msg) {
    sf::IpAddress recipient = ipAddress;

    if (m_socket.send(msg.c_str(), msg.size(), recipient, port) != sf::Socket::Done)
    {
//         Erreur
        std::cout << "Erreur dans l'envoie du message" << std::endl;
    }

    std::cout << "MESSAGE SENDED" << std::endl;
}

void Socket::send(std::string ipAddress, int port, Serializable *serializable) {
    send(ipAddress, port, serializable->serialize());
}
