#ifndef __SOCKET_HPP__
#define __SOCKET_HPP__

#include <string>

#include <SFML/Network.hpp>

#include "Serializable.hpp"

namespace plb {
    class Socket {
    public:
        Socket(int port);

        int getPort() const;

        std::string receive();
        std::string receive(int timeout);

        void send(std::string ipAddress, int port, std::string msg);
        void send(std::string ipAddress, int port, Serializable* serializable);
    private:
        int m_port;
        sf::UdpSocket m_socket;
    };
}

#endif /* __SOCKET_HPP__ */
