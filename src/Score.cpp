#include <SFML/Graphics/RectangleShape.hpp>

#include "Score.hpp"
#include "Game.hpp"
#include "Color.hpp"

Score::Score() {
    // TODO : Tempory
    m_x = 300;
    m_y = 0;
    m_height = 100;
    m_width = 300;
}

Score::~Score() {
    delete this;
}

Score::Score(unsigned int x, unsigned int y) {
    m_x = x;
    m_y = y;
    m_height = 80;
    m_width = 419;
}

Score::Score(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
    m_x = x;
    m_y = y;
    m_height = height;
    m_width = width;
}



void Score::draw() const {
    std::cout << "SCORE DRAW" << std::endl;
    sf::RectangleShape rectangle(sf::Vector2f(m_width, m_height));
    rectangle.move(m_x, m_y);
    rectangle.setFillColor(sf::Color::White);
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

    score.setString(m_power);

    //text.setStyle(sf::Text::Bold);


    Game::m_main_window.draw(name);
    Game::m_main_window.draw(score);
}
