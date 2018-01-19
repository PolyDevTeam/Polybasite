#ifndef __MINER_HPP__
#define __MINER_HPP__

#include "Entity.hpp"

class Miner : public Entity {
public:
    Miner(unsigned x, unsigned y);
    virtual ~Miner();

    virtual void draw() const;

    std::string serialize();
    void deserialize(std::string serializable);
};

#endif /* __MINER_HPP__ */
