#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Serializable.hpp"

using namespace sf;

class Bot;
class Miner;

class Entity : public Sprite, public Serializable {
public:
    static const unsigned ENTITY_WIDTH = 20;
    static const unsigned ENTITY_HEIGHT = 20;

    Entity();
    Entity(unsigned x, unsigned y);
    unsigned getX() const;
    unsigned getY() const;

    virtual ~Entity();

    virtual void draw() const;

    virtual std::string serialize();
    virtual void deserialize(std::string &serializable);
    virtual void interact(Miner* miner);
    virtual unsigned getPower() const;
protected:
    unsigned m_x;
    unsigned m_y;
};

#endif /* __ENTITY_HPP__ */
