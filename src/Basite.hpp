#ifndef __BASITE_HPP__
#define __BASITE_HPP__

#include "Entity.hpp"

class Basite : public Entity {
public:
    static const unsigned MAX_POWER = 8;

    Basite(unsigned x, unsigned y, unsigned power);
    virtual void draw() const;
    virtual ~Basite();

private:
    unsigned m_x;
    unsigned m_y;
    unsigned m_power;
};

#endif /* __BASITE_HPP__ */
