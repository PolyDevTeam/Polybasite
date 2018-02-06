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
    setEntity(new Miner(0, 0, 2));
    setEntity(new Miner(0, 1, 6));
    setEntity(new Miner(0, 2, 7));

    setEntity(new Miner(1, 0, 5));
    setEntity(new Miner(1, 1, 5));
    setEntity(new Miner(1, 2, 8));

}

void Map::update() {
    std::cout << "ACTION" <<std::endl;

    // Mineur 1 a + b < 8
    Miner *m10 = (Miner *)m_entities[1][0];
    std::cout << "miner 1 power = "<< m10->getPower() << std::endl;

    Miner *m00 = (Miner *)m_entities[0][0];
    std::cout << "miner 0 power = "<< m00->getPower() << std::endl;


    m10->setPower(m00->getPower() + m10->getPower());
    m00->setPower(0);
    std::cout << "new miner 1 power = "<< m10->getPower() << std::endl;


    // Mineur 2 a + b => 8
    Miner *m11 = (Miner *)m_entities[1][1];
    std::cout << "miner 3 power = "<< m11->getPower() << std::endl;

    Miner *m01 = (Miner *)m_entities[0][1];
    std::cout << "miner 2 power = "<< m01->getPower() << std::endl;

    unsigned p = (m11->getPower() + m01->getPower());
    if (p >= 8){
        m11->setPower(8);
        m01->setPower(p%8);
        std::cout << "new miner 3 power = "<< m11->getPower() << std::endl;
        std::cout << "new miner 2 power = "<< m01->getPower() << std::endl;

    }


    // Mineur 3 a = 8 | b = 8
    Miner *m12 = (Miner *)m_entities[1][2];
    std::cout << "miner 5 power = "<< m12->getPower() << std::endl;

    Miner *m02 = (Miner *)m_entities[0][2];
    std::cout << "miner 4 power = "<< m02->getPower() << std::endl;

    if (m12->getPower() >= 8){
        // power is over the limit -> can't send power
        // nothing appen
        std::cout << "new miner 5 power = "<< m12->getPower() << std::endl;
        std::cout << "new miner 4 power = "<< m02->getPower() << std::endl;

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

Entity* Map::getEntity(unsigned x, unsigned y){
    Entity *e = m_entities[x][y];
    return e;
}

void Map::setEntity(Entity *entity) {
    m_entities[entity->getX()][entity->getY()] = entity;
}
