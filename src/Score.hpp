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

    void draw() const;

private:
    unsigned m_x;
    unsigned m_y;

    unsigned m_height;
    unsigned m_width;
};

#endif /* __SCORE_HPP__ */
