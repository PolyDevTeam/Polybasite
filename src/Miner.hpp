#ifndef __MINER_HPP__
#define __MINER_HPP__

#include "Entity.hpp"

class Miner : public Entity {
public:
    static const unsigned MAX_POWER = 8;

    Miner(unsigned x, unsigned y);
    virtual ~Miner();

    virtual void draw() const;

    std::string serialize();
    void deserialize(std::string serializable);

    void setPower(unsigned power);
    unsigned getPower() const;

    bool operator==(const Miner& m);
private:
    unsigned m_power;
};

#endif /* __MINER_HPP__ */
