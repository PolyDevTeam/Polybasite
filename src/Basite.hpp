#ifndef __BASITE_HPP__
#define __BASITE_HPP__

#include "Entity.hpp"

class Basite : public Entity {
public:
    virtual void draw() const;
    virtual ~Basite();
};

#endif /* __BASITE_HPP__ */
