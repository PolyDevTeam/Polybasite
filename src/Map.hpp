#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <vector>
#include "Entity.hpp"

using namespace std;

// TODO : Add some polymorphism for entities

class Map {
public:
    Map() {
        // TODO : Tempory
        Entity entity;
        m_entities.push_back(entity);
    }

    void draw() const;
private:
    vector<Entity> m_entities;
    unsigned m_height;
    unsigned m_width;
};

#endif /* __MAP_HPP__ */
