#include <iostream>
#include <unistd.h>

//#include "hlt.hpp"
//#include "networking.hpp"

//#include <../../src/Socket.hpp>

#include <string>

#include <SFML/Network.hpp>

// TODO : Tempory code it's just a copy from Polybasite code
namespace plb {
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
//    char name[100] = msg.c_str();
//    sf::UdpSocket socket;
            sf::IpAddress recipient = /*"127.0.0.1"*/ipAddress;
//    unsigned short port = 55555;
            if (m_socket.send(msg.c_str(), 100, recipient, port) != sf::Socket::Done)
            {
//         Erreur
                std::cout << "Erreur dans l'envoie du message" << std::endl;
            }

            std::cout << "MESSAGE SENDED" << std::endl;
        }
    private:
        int m_port;
        sf::UdpSocket m_socket;
    };
}

// NETWORKING HEADER CODE
plb::Socket *socket = new plb::Socket(0);

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

int main(int argc, char* argv[]) {
    if(argc != 3)
        return -1;

    sleep(3);

    std::cout << "HELLO WORLD" << std::endl;

    // TODO : Unserialize map function
    // TODO : Send miner movements

    initBot("RandomBot", argv);

    std::cout << "FIN BOT" << std::endl;

    return 0;
}