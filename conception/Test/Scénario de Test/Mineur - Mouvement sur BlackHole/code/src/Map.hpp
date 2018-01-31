#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <vector>

#include "Entity.hpp"

using namespace std;

typedef std::vector<Entity*> VEntity;

class Map {
public:
    static const unsigned OFFSET_X = 0;
    static const unsigned OFFSET_Y = 50;

    Map(unsigned width, unsigned height);
    ~Map();
    void draw() const;
    void setEntity(Entity* entity);
    Entity* getEntity(unsigned x, unsigned y);
    void update();

    unsigned getHeight() const;
    unsigned getWidth() const;
private:
    std::vector<std::vector<Entity*>> m_entities;
    unsigned m_width;
    unsigned m_height;
};

#endif /* __MAP_HPP__ */
