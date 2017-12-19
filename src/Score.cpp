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

}

Score::Score(unsigned int x, unsigned int y) {
    // TODO : Tempory
    m_x = x;
    m_y = y;
    m_height = 100;
    m_width = 300;
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

    sf::Text text;

    text.setFont(font);
    text.setString("Score Total = " + std::to_string(42));
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    //text.setStyle(sf::Text::Bold);

    text.move(m_x + 10, m_y + 10);

    Game::m_main_window.draw(text);
}
