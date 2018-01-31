#ifndef __MINER_HPP__
#define __MINER_HPP__

#include "Entity.hpp"

class Miner : public Entity {
public:
    static const unsigned MAX_POWER = 8;
    Miner(unsigned x, unsigned y, unsigned power);
    virtual ~Miner();

    virtual void draw() const;
    unsigned int getPower() const;
    void setPower(unsigned int power);

private:
    unsigned m_power;
};

#endif /* __MINER_HPP__ */
