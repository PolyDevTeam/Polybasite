#ifndef __BLACKHOLE_HPP__
#define __BLACKHOLE_HPP__

#include "Entity.hpp"

class BlackHole : public Entity {
public:
    static const unsigned BLACK_HOLE_PROB = 5;

    BlackHole(unsigned x, unsigned y);
    virtual ~BlackHole();

    virtual void draw() const;
};

#endif /* __BLACKHOLE_HPP__ */