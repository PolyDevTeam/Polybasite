#include <iostream>
#include <vector>
#include <sstream>

#include <SFML/Graphics/RectangleShape.hpp>

#include "Game.hpp"
#include "Map.hpp"
#include "Basite.hpp"
#include "BlackHole.hpp"
#include "Bot.hpp"

Map::Map(unsigned width, unsigned height) {
    m_width = width;
    m_height = height;
    m_blackHoleNumber = 0;
    createMap();
}

Map::~Map() {
    for (unsigned i = 0; i < m_entities.size(); ++i) {
        for (unsigned j = 0; j < m_entities[i].size(); ++j) {
            delete m_entities[i][j];
            m_entities[i][j] = 0;
        }
    }
}

std::vector<Entity *> & Map::operator[](unsigned i) {
    return m_entities[i];
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

std::string Map::serialize() {
    std::ostringstream os;
    os << "Map:" << m_width << ";" << m_height << ";";

    for(unsigned i = 0; i < m_width; ++i) {
        for(unsigned j = 0; j < m_height; ++j) {
            os << m_entities[i][j]->serialize() << ";";
        }
    }

    return os.str();
}

void Map::deserialize(std::string &serializable) {
    std::string buff;

    buff = serializable.substr(0, serializable.find(":", 0));
    serializable = serializable.substr(serializable.find(":", 0)+1, serializable.length());

    if(buff != "Map") {
        std::cout << buff << std::endl;
        std::cout << "Ce n'est pas un objet map" << std::endl;
        return;
    }

    buff = serializable.substr(0, serializable.find(";", 0));
    serializable = serializable.substr(serializable.find(";", 0)+1, serializable.length());
    m_width = atoi(buff.c_str());

    buff = serializable.substr(0, serializable.find(";", 0));
    serializable = serializable.substr(serializable.find(";", 0)+1, serializable.length());
    m_height = atoi(buff.c_str());

    for (unsigned i = 0; i < m_width; ++i) {
        VEntity line;

        for (unsigned j = 0; j < m_height; ++j) {
            buff = serializable.substr(0, serializable.find(":", 0));

            if(buff == "Entity") {
                Entity* entity = new Entity();
                entity->deserialize(serializable);
                line.push_back(entity);
            }
            else if(buff == "BlackHole") {
                BlackHole* blackHole = new BlackHole();
                blackHole->deserialize(serializable);
                line.push_back(blackHole);
            }
            else if(buff == "Basite") {
                Basite* basite = new Basite();
                basite->deserialize(serializable);
                line.push_back(basite);
            }
            else if(buff == "Miner") {
                Miner* miner = new Miner();
                miner->deserialize(serializable);
                line.push_back(miner);
            }
        }

        m_entities.push_back(line);
    }
}

void Map::createMap() {
    for (unsigned i = 0; i < m_width; ++i) {
        VEntity line;

        for (unsigned j = 0; j < m_height; ++j) {
            unsigned prob = rand() % 100;

            if (prob <= BlackHole::BLACK_HOLE_PROB) {
                m_blackHoleNumber++;
                line.push_back(new BlackHole(i, j));
            } else {
                unsigned power = rand() % (Basite::MAX_POWER - Basite::MIN_POWER) + Basite::MIN_POWER;
                line.push_back(new Basite(i, j, power));
            }
        }

        m_entities.push_back(line);
    }
}

void Map::clear() {
    m_entities.clear();
    createMap();
}

unsigned Map::getPower() const {
    unsigned power = 0;

    for(unsigned i = 0; i < m_width; ++i) {
        for(unsigned j = 0; j < m_height; ++j) {
            Entity* entity = m_entities[i][j];
            power = power + entity->getPower();
        }
    }

    return power;
}

unsigned Map::getBlackHoleNumber() const {
    return m_blackHoleNumber;
}