#ifndef __MOVE_HPP__
#define __MOVE_HPP__

#include <vector>
#include <sstream>

#include "Serializable.hpp"
#include "Miner.hpp"

enum DIRECTIONS {
    STILL = 0,
    NORTH = 1,
    EAST = 2,
    SOUTH = 3,
    WEST = 4,
};

class Move : public Serializable {
public:
    Move();
    Move(unsigned minerId, DIRECTIONS directions);

    virtual ~Move();
    virtual std::string serialize();
    virtual void deserialize(std::string &serializable);

    void move(std::vector<Miner*> &miners) const;

    bool operator<(const Move& move) const;
    Move& operator=(const Move& move);

    DIRECTIONS m_directions;
    unsigned m_minerId;
};

#endif /* __MOVE_HPP__ */
