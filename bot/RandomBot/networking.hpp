#ifndef __NETWORKING_HPP__
#define __NETWORKING_HPP__

#include <iostream>
#include <set>

#include <SFML/Network.hpp>

#include "plb.hpp"

// TODO : Add code with error exception
namespace plb {
    class Socket {
    public:
        Socket(int port) : m_port(port), m_socket() {
            srand(time(NULL)); // Rand initialisation

            // Default constructor is prohibited by SFML
            if(port == 0) {
                m_port = rand() % (65535 - 49152) + 49152; // Free port range
            }

            if(m_socket.bind(m_port) != sf::Socket::Done) {
                // TODO : Have a good error method for log and try catch it
                std::cerr << "Error to create an socket" << std::endl;
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
                // TODO : Create error
            }

            return std::string(data);
        }

        void send(std::string ipAddress, int port, std::string msg) {
            sf::IpAddress recipient = ipAddress;

            if (m_socket.send(msg.c_str(), msg.size(), recipient, port) != sf::Socket::Done) {
                // TODO : Create error
                std::cerr << "Sending error" << std::endl;
            }
        }
    private:
        int m_port;
        sf::UdpSocket m_socket;
    };
}

static plb::Socket *socket = new plb::Socket(0);
static int port_server;

static void initBot(std::string botName, char* argv[], plb::Map &map) {
    // TODO : Prevent bot got ; in his name
    // TODO : Prevent if port number is already taken by an another bot

    // Send bot name to the main thread
    port_server = atoi(argv[1]);
    plb::ownerId = atoi(argv[2]);
    socket->send("127.0.0.1", port_server, botName + ";" + std::to_string(socket->getPort()));

    // Receive the game map
    std::string mapString = socket->receive();

    // Deserialize Map
    map.deserialize(mapString);
}

static void getFrame(plb::Map &map) {
    std::string mapString  = socket->receive();
    map.deserialize(mapString);
}

static void sendFrame(std::set<plb::Move> moves) {
    std::string moveString = "";

    for(plb::Move move : moves) {
        moveString += move.serialize();
    }

    moveString += '\0';
    socket->send("127.0.0.1", port_server, moveString);
}

#endif /* __NETWORKING_HPP__ */
