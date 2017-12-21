#ifndef __SCORE_HPP__
#define __SCORE_HPP__

#include <vector>

#include "Entity.hpp"
#include "Basite.hpp"
#include "Bot.hpp"

using namespace std;

class Score {
public:
    Score();
    ~Score();

    Score(unsigned int x, unsigned int y);
    Score(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

    void draw() const;

    //TODO : Méthode get nom du Bot
    //TODO : méthode get score / puissance

private:
    unsigned m_x;
    unsigned m_y;

    unsigned m_height;
    unsigned m_width;

    unsigned m_power;
    unsigned m_name;
};

#endif /* __SCORE_HPP__ */
