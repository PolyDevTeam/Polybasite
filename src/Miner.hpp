#ifndef __MINER_HPP__
#define __MINER_HPP__

#include "Entity.hpp"
#include "Color.hpp"

class Miner : public Entity {
public:
    static const unsigned MAX_POWER = 8;

    Miner();
    Miner(unsigned owner, unsigned x, unsigned y);
    virtual ~Miner();

    virtual void draw() const;

    std::string serialize();
    void deserialize(std::string &serializable);

    void setPower(unsigned power);
    unsigned getPower() const;
    void setColor(sf::Color color);

    bool operator==(const Miner& m);

    unsigned getOwner() const;

    void interact(Miner *miner);
private:
    unsigned m_owner;
    unsigned m_power;
    sf::Color m_color;
};

#endif /* __MINER_HPP__ */
