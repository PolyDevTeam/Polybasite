#ifndef __NETWORKING_HPP__
#define __NETWORKING_HPP__

#include <iostream>

#include <SFML/Network.hpp>

// TODO : Add code with error exception
// TODO : Tempory code it's just a copy from Polybasite code Update it when the original is modified
namespace plb {
    // TODO : Update this class with the current class in main project
    class Socket {
    public:
        Socket(int port) : m_port(port), m_socket() {
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

        int getPort() const {
            return m_port;
        }

        std::string receive() {
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

        void send(std::string ipAddress, int port, std::string msg) {
            sf::IpAddress recipient = ipAddress;

            if (m_socket.send(msg.c_str(), msg.size(), recipient, port) != sf::Socket::Done) {
                // Erreur
                std::cout << "Erreur dans l'envoie du message" << std::endl;
            }

            std::cout << "MESSAGE SENDED" << std::endl;
        }
    private:
        int m_port;
        sf::UdpSocket m_socket;
    };
}

static plb::Socket *socket = new plb::Socket(0);

void initBot(std::string botName, char* argv[]) {
    // TODO : Prevent bot got ; in his name
    // TODO : Prevent if port number is already taken by an another bot

    // Send bot name to the main thread
    socket->send("127.0.0.1", atoi(argv[1]), botName + ";" + std::to_string(socket->getPort()));

    // Receive the game map
    std::string mapString = socket->receive();

    // TODO : Unserialize Map

    // TODO : Create an object MAP
}

#endif /* __NETWORKING_HPP__ */
