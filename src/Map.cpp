#include "Map.hpp"

Map::Map() {
    // TODO : Tempory
    unsigned MAP_HEIGHT = 30;
    unsigned MAP_WIDTH = 30;
    unsigned max = 8;
    unsigned min = 1;

    srand(time(NULL)); // initialisation de rand

    for (unsigned i = 0; i < MAP_WIDTH; ++i) {
        for (unsigned j = 0; j < MAP_HEIGHT; ++j) {
            unsigned power = rand()%(max-min) + min;
            m_entities.push_back(new Basite(i, j, power));
        }
    }
}

Map::~Map() {
    for(unsigned i = 0; i < m_entities.size(); ++i) {
        delete m_entities[i];
        m_entities[i] = 0;
    }
}

void Map::draw() const {
    for (unsigned i = 0; i < m_entities.size(); ++i) {
        Entity *entity = m_entities[i];
        entity->draw();
    }
}
