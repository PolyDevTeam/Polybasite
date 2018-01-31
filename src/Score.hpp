#ifndef __SCORE_HPP__
#define __SCORE_HPP__

#include "Bot.hpp"

using namespace std;

class Score {
public:
    static const unsigned SCORE_OFFSET_X = 605;
    static const unsigned SCORE_OFFSET_Y = 75;
    static const unsigned SCORE_WIDTH = 420;
    static const unsigned SCORE_HEIGHT = 100;

    Score(unsigned int position, Bot* bot);
    ~Score();
    void draw() const;
private:
    unsigned m_position;
    Bot* m_bot;
};

#endif /* __SCORE_HPP__ */
