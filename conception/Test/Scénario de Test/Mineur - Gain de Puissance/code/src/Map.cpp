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

    Miner *m10 = (Miner *)m_entities[1][0];
    std::cout << "miner 1 power = "<< m10->getPower() << std::endl;

    Miner *m00 = (Miner *)m_entities[0][0];
    std::cout << "miner 0 power = "<< m00->getPower() << std::endl;

    Miner *m11 = (Miner *)m_entities[1][1];
    std::cout << "miner 3 power = "<< m11->getPower() << std::endl;

    Miner *m01 = (Miner *)m_entities[0][1];
    std::cout << "miner 2 power = "<< m01->getPower() << std::endl;

    Miner *m12 = (Miner *)m_entities[1][2];
    std::cout << "miner 5 power = "<< m12->getPower() << std::endl;

    Miner *m02 = (Miner *)m_entities[0][2];
    std::cout << "miner 4 power = "<< m02->getPower() << std::endl;

    if (m00->getPower() < 8){
        m00->setPower(m00->getPower()+1);
    }

    if (m01->getPower() < 8){
        m01->setPower(m01->getPower()+1);
    }

    if (m02->getPower() < 8){
        m02->setPower(m02->getPower()+1);
    }

    if (m10->getPower() < 8){
        m10->setPower(m10->getPower()+1);
    }

    if (m11->getPower() < 8){
        m11->setPower(m11->getPower()+1);
    }

    if (m12->getPower() < 8){
        m12->setPower(m12->getPower()+1);
    }

    std::cout << "new miner 1 power = "<< m10->getPower() << std::endl;
    std::cout << "new miner 0 power = "<< m00->getPower() << std::endl;
    std::cout << "new miner 3 power = "<< m11->getPower() << std::endl;
    std::cout << "new miner 2 power = "<< m01->getPower() << std::endl;
    std::cout << "new miner 5 power = "<< m12->getPower() << std::endl;
    std::cout << "new miner 4 power = "<< m02->getPower() << std::endl;

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
