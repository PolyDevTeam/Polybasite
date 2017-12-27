#ifndef __SCORE_HPP__
#define __SCORE_HPP__

#include <vector>
#include <string>

#include "Entity.hpp"
#include "Basite.hpp"
#include "Bot.hpp"

using namespace std;

class Score {
public:
    ~Score();
    Score(unsigned int i, std::string name, unsigned* power, sf::Color color);
    void draw() const;

    //TODO : Méthode get nombre de bot
    //TODO : Méthode get Couleur du Bot
    //TODO : Méthode get nom du Bot
    //TODO : méthode get score / puissance

private:
    unsigned m_x;
    unsigned m_y;

    unsigned m_height;
    unsigned m_width;

    unsigned* m_power;
    std::string m_name;
    sf::Color m_color;
};

#endif /* __SCORE_HPP__ */
