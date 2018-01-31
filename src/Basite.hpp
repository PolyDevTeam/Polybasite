#ifndef __BASITE_HPP__
#define __BASITE_HPP__

#include "Entity.hpp"
#include "Bot.hpp"

class Basite : public Entity {
public:
    static const unsigned MAX_POWER = 8;

    Basite();
    Basite(unsigned x, unsigned y, unsigned power);
    virtual ~Basite();

    virtual void draw() const;
    virtual std::string serialize();
    virtual void deserialize(std::string &serializable);
    void interact(Miner *miner);
    unsigned getPower() const;
private:
    unsigned m_power;
};

#endif /* __BASITE_HPP__ */
