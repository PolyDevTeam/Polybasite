#ifndef __BLACKHOLE_HPP__
#define __BLACKHOLE_HPP__

#include <SFML/Graphics/Sprite.hpp>

#include "Entity.hpp"

class BlackHole : public Entity {
public:
    static const unsigned BLACK_HOLE_PROB = 5;

    BlackHole();
    BlackHole(unsigned x, unsigned y);
    virtual ~BlackHole();

    virtual void draw() const;

    virtual std::string serialize();
    virtual void deserialize(std::string &serializable);
    virtual void interact(Miner *miner);
    unsigned getPower() const;

    static sf::Texture m_texture;
    static unsigned m_rotation;
};

#endif /* __BLACKHOLE_HPP__ */
