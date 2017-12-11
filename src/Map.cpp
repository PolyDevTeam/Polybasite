#include "Map.hpp"

void Map::draw() const {
    for(unsigned i = 0; i < m_entities.size(); ++i) {
        Entity* entity = m_entities[i];
        entity->draw();
    }
}
