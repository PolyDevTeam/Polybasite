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
    setEntity(new Miner(0, 0, 5, sf::Color::Red));
    setEntity(new Miner(0, 1, 1, sf::Color::Red));
    setEntity(new Miner(0, 2, 3, sf::Color::Red));

    setEntity(new Miner(1, 0, 1, sf::Color::Cyan));
    setEntity(new Miner(1, 1, 5, sf::Color::Cyan));
    setEntity(new Miner(1, 2, 3, sf::Color::Cyan));

}

void Map::update() {
    std::cout << "ACTION" <<std::endl;

    // Mineur1 > Mineur2
    Miner *m10 = (Miner *)m_entities[1][0];
    std::cout << "basite power = "<< m10->getPower() << std::endl;

    Miner *m00 = (Miner *)m_entities[0][0];
    std::cout << "miner power = "<< m00->getPower() << std::endl;

    if (m00->getPower() > m10->getPower()){
        setEntity(new Miner(1, 0, m00->getPower() - m10->getPower(), sf::Color::Red));
        m00->setPower(0);
    }

    // Mineur1 < Mineur2
    Miner *m11 = (Miner *)m_entities[1][1];
    std::cout << "basite power = "<< m10->getPower() << std::endl;

    Miner *m01 = (Miner *)m_entities[0][1];
    std::cout << "miner power = "<< m00->getPower() << std::endl;

    if (m11->getPower() > m01->getPower()){
        setEntity(new Miner(0, 1, m11->getPower() - m01->getPower(), sf::Color::Cyan));
        m11->setPower(0);
    }

    // Mineur1 = Mineur2
    Miner *m12 = (Miner *)m_entities[1][2];
    std::cout << "basite power = "<< m10->getPower() << std::endl;

    Miner *m02 = (Miner *)m_entities[0][2];
    std::cout << "miner power = "<< m00->getPower() << std::endl;

    if (m12->getPower() == m02->getPower()){
        setEntity(new Basite(0, 2, 0));
        setEntity(new Basite(1, 2, 0));

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
