#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

using namespace sf;

class Entity : Sprite {
public:
    static const unsigned ENTITY_WIDTH = 16;
    static const unsigned ENTITY_HEIGHT = 16;

    Texture m_texture;

    void draw() const;
};

#endif /* __ENTITY_HPP__ */