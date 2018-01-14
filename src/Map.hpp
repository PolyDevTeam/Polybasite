#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <vector>

#include "Entity.hpp"
#include "Serializable.hpp"

using namespace std;

typedef std::vector<Entity*> VEntity;

class Map : public Serializable {
public:
    static const unsigned OFFSET_X = 0;
    static const unsigned OFFSET_Y = 50;

    Map(unsigned width, unsigned height);
    virtual ~Map();
    void draw() const;
    void setEntity(Entity* entity);

    unsigned getHeight() const;
    unsigned getWidth() const;

    virtual std::string serialize();
    void deserialize(std::string serializable);
private:
    std::vector<std::vector<Entity*>> m_entities;
    unsigned m_width;
    unsigned m_height;
};

#endif /* __MAP_HPP__ */
