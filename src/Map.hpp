#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <vector>

#include "Entity.hpp"

using namespace std;

class Map {
public:
    Map();
    ~Map();
    void draw() const;
private:
    vector<Entity*> m_entities;
    unsigned m_height;
    unsigned m_width;
};

#endif /* __MAP_HPP__ */
