#ifndef __BOT_HPP__
#define __BOT_HPP__

#include <string>
#include <vector>

#include "Miner.hpp"
#include "Color.hpp"

using namespace std;

class Bot {
public:
    Bot(string name, unsigned x, unsigned y);
    virtual ~Bot();
    string getName() const;
private:
    string m_name;
    unsigned m_owner;
    ::Color m_color;
    vector<Miner*> m_miners;
};

#endif /* __BOT_HPP__ */
