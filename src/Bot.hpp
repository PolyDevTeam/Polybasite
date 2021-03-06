#ifndef __BOT_HPP__
#define __BOT_HPP__

#include <string>
#include <vector>
#include <thread>

#include "Miner.hpp"
#include "Color.hpp"
#include "Socket.hpp"

using namespace std;

class Bot {
public:
    Bot(string name, unsigned x, unsigned y, unsigned id);
    virtual ~Bot();
    string getName() const;
    sf::Color getColor() const;
    void setColor(sf::Color color);
    void turn();
    void addMiner(unsigned x, unsigned y, unsigned power);
    void deleteMiner(Miner* miner);
    unsigned getOwner() const;
    unsigned getMinerNumber() const;
    unsigned getPower() const;
    void stopBot();
private:
    Bot(const Bot& bot); // std::thread isn't copyable

    string m_name;
    unsigned m_owner;
    sf::Color m_color;
    vector<Miner*> m_miners;

    plb::Socket* m_socket;
    std::thread m_instance;
    unsigned m_port;
};

#endif /* __BOT_HPP__ */
