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

void Map::deserialize(std::string serializable) {
    std::string str = serializable;
    std::string buff;

    buff = str.substr(0, str.find(":", 0));
    str = str.substr(str.find(":", 0)+1, str.length());

    if(buff != "Map") {
        std::cout << buff << std::endl;
        std::cout << "Ce n'est pas un objet map" << std::endl;
        return;
    }

    buff = str.substr(0, str.find(";", 0));
    str = str.substr(str.find(";", 0)+1, str.length());
    m_width = atoi(buff.c_str());

    buff = str.substr(0, str.find(";", 0));
    str = str.substr(str.find(";", 0)+1, str.length());
    m_height = atoi(buff.c_str());

    for (unsigned i = 0; i < m_width; ++i) {
        VEntity line;

        for (unsigned j = 0; j < m_height; ++j) {
            buff = str.substr(0, str.find(":", 0));

            if(buff == "Entity") {
                Entity* entity = new Entity();
                entity->deserialize(str);
                line.push_back(entity);
            }
            else if(buff == "BlackHole") {
                BlackHole* blackHole = new BlackHole();
                blackHole->deserialize(str);
                line.push_back(blackHole);
            }
            else if(buff == "Basite") {
                Basite* basite = new Basite();
                basite->deserialize(str);
                line.push_back(basite);
            }
        }

        m_entities.push_back(line);
    }
}