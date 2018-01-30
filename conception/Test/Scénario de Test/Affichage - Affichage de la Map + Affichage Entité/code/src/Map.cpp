#include <iostream>
#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>

#include "Game.hpp"
#include "Map.hpp"
#include "Basite.hpp"
#include "BlackHole.hpp"
#include "Miner.hpp"

Map::Map(unsigned width, unsigned height) {
    m_width = width;
    m_height = height;

    // TODO : Tempory
    unsigned max = 8;
    unsigned min = 1;

    for (unsigned i = 0; i < m_width; ++i) {
        VEntity line;

        for (unsigned j = 0; j < m_height; ++j) {
            unsigned prob = rand() % 100;

            if (prob <= BlackHole::BLACK_HOLE_PROB) {
                line.push_back(new BlackHole(i, j));
            } else {
                unsigned power = rand() % (max - min) + min;
                line.push_back(new Basite(i, j, power));
            }
        }

        m_entities.push_back(line);
    }

    for (unsigned j = 0; j < m_height; j++) {
        for (unsigned i = 0; i < m_width; i++) {
            unsigned prob = rand() % 100;
            if (prob < 20) {
                setEntity(new Miner(i, j));
            }
        }
    }

}

Map::~Map() {
    for (unsigned i = 0; i < m_entities.size(); ++i) {
        for (unsigned j = 0; j < m_entities[i].size(); ++j) {
            delete m_entities[i][j];
            m_entities[i][j] = 0;
        }
    }
}

unsigned Map::getWidth() const {
    return m_width;
}

unsigned Map::getHeight() const {
    return m_height;
}

void Map::draw() const {
    for (unsigned i = 0; i < m_entities.size(); ++i) {
        for (unsigned j = 0; j < m_entities[i].size(); ++j) {
            Entity *entity = m_entities[i][j];
            entity->draw();
        }
    }
}

void Map::setEntity(Entity *entity) {
    m_entities[entity->getX()][entity->getY()] = entity;
}
