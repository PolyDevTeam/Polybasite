#include <SFML/Graphics/RectangleShape.hpp>

#include "Score.hpp"
#include "Game.hpp"
#include "Color.hpp"


Score::~Score() {
    delete this;
}

Score::Score(unsigned int i, std::string name, unsigned* power, sf::Color color) {
    // Dimension for 4 Score + 1 total
    m_width = 419;
    m_height = 100;
    m_x = 605;
    // n°eme bot * (ScoreSize + spaceBetween)  + offset up
    m_y = i * (m_height + 10) + 50;
    m_name = name;
    m_power = power;
    m_color = color;
}


void Score::draw() const {
    sf::RectangleShape rectangle(sf::Vector2f(m_width, m_height));
    rectangle.move(m_x, m_y);
    rectangle.setFillColor(m_color);
    Game::m_main_window.draw(rectangle);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "ERROR : FONT NOT FOUND" << std::endl;
    }

    sf::Text name;
    name.setFont(font);
    name.setCharacterSize(18);
    name.setFillColor(sf::Color::Red);
    name.move(m_x + 5, m_y + 5);

    name.setString(m_name);

    sf::Text score;
    score.setFont(font);
    score.setCharacterSize(16);
    score.setFillColor(sf::Color::Black);
    score.move(m_x + 5, m_y + 35);

    score.setString(std::to_string(*m_power));


    //std::cout << "SCORE DRAW" << std::endl;
    //std::cout << *m_power << std::endl;

    Game::m_main_window.draw(name);
    Game::m_main_window.draw(score);
}
