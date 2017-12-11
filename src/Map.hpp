#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <vector>

#include "Entity.hpp"
#include "Basite.hpp"
#include "Bot.hpp"

using namespace std;

class Map {
public:
    Map() {
        // TODO : Tempory
        m_entities.push_back(new Basite);
    }

    ~Map() {
        for(unsigned i = 0; i < m_entities.size(); ++i) {
            delete m_entities[i];
            m_entities[i] = 0;
        }
    }

    void draw() const;
private:
    vector<Entity*> m_entities;
    unsigned m_height;
    unsigned m_width;
};

#endif /* __MAP_HPP__ */
