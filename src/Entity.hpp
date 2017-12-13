#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

using namespace sf;

class Entity : public Sprite {
public:
    static const unsigned ENTITY_WIDTH = 20;
    static const unsigned ENTITY_HEIGHT = 20;

    Texture m_texture;

    virtual void draw() const;
    virtual ~Entity();
};

#endif /* __ENTITY_HPP__ */
