#ifndef __BOT_HPP__
#define __BOT_HPP__

#include "Entity.hpp"

class Bot : public Entity {
public:
    virtual void draw() const;
    virtual ~Bot();
};

#endif /* __BOT_HPP__ */
