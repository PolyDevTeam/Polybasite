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


    for (unsigned i = 0; i < m_width; ++i) {
        VEntity line;

        for (unsigned j = 0; j < m_height; ++j) {
                line.push_back(new Basite(i, j, 0));
        }

        m_entities.push_back(line);
    }
    setEntity(new Miner(0, 0, 8));
    setEntity(new BlackHole(1, 0));


}

void Map::update() {
    std::cout << "ACTION" <<std::endl;

    // BlackHole always wins
    BlackHole *b = (BlackHole *)m_entities[1][0];

    Miner *m = (Miner *)m_entities[0][0];
    std::cout << "miner power = "<< m->getPower() << std::endl;


    setEntity(new Basite(m->getX(), m->getY(), 0));

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

Entity* Map::getEntity(unsigned x, unsigned y){
    Entity *e = m_entities[x][y];
    return e;
}

void Map::setEntity(Entity *entity) {
    m_entities[entity->getX()][entity->getY()] = entity;
}
