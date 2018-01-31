#include <SFML/Graphics/RectangleShape.hpp>

#include "Score.hpp"
#include "Game.hpp"
#include "RichText.hpp"
#include "ProgressBar.hpp"

Score::Score(unsigned int position, Bot *bot) : m_position(position), m_bot(bot){

}

Score::~Score() {

}

void Score::drawLegend() {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "ERROR : FONT NOT FOUND" << std::endl;
    }

    RichText territoryPercentText(font);
    territoryPercentText.setCharacterSize(20);
    territoryPercentText << "Territory percent : ";
    territoryPercentText.move((Game::SCREEN_WIDTH - SCORE_WIDTH/2) - territoryPercentText.getLocalBounds().width, Game::SCREEN_HEIGHT - SCORE_HEIGHT);

    sf::RectangleShape rectangleTerritory(sf::Vector2f(50, 20));
    rectangleTerritory.setFillColor(sf::Color(255,239,229));
    rectangleTerritory.move((Game::SCREEN_WIDTH - SCORE_WIDTH/2) + 10, Game::SCREEN_HEIGHT - SCORE_HEIGHT + 2);

    Game::m_main_window.draw(rectangleTerritory);
    Game::m_main_window.draw(territoryPercentText);

    RichText powerPercentText(font);
    powerPercentText.setCharacterSize(20);
    powerPercentText << "Power percent : ";
    powerPercentText.move((Game::SCREEN_WIDTH - SCORE_WIDTH/2) - powerPercentText.getLocalBounds().width, Game::SCREEN_HEIGHT - SCORE_HEIGHT + 30);

    sf::RectangleShape rectanglePower(sf::Vector2f(50, 20));
    rectanglePower.setFillColor(sf::Color(111, 177, 207));
    rectanglePower.move((Game::SCREEN_WIDTH - SCORE_WIDTH/2) + 10, Game::SCREEN_HEIGHT - SCORE_HEIGHT + 30 + 2);

    Game::m_main_window.draw(rectanglePower);
    Game::m_main_window.draw(powerPercentText);
}

void Score::draw() const {
    unsigned x = SCORE_OFFSET_X;
    unsigned y = m_position * (SCORE_HEIGHT + 10) + SCORE_OFFSET_Y;

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "ERROR : FONT NOT FOUND" << std::endl;
    }

    // Display bot's name
    y += 10;

    RichText name(font);
    name.setCharacterSize(20);
    name << m_bot->getColor() << m_bot->getName() << " : ";
    name.move(x, y);
    Game::m_main_window.draw(name);

    // Display territory percent
    unsigned mapTerritory = (Game::m_map.getWidth() * Game::m_map.getHeight()) - Game::m_map.getBlackHoleNumber();
    float percentTerritory = ((float) m_bot->getMinerNumber() / (float) mapTerritory)*100.0f;

    x += 20;
    y += 40;

    ProgressBar territoryBar(percentTerritory);
    territoryBar.setShowBackgroundAndFrame(true);
    territoryBar.setSize({ SCORE_WIDTH - 40.0f, 20.f });
    territoryBar.move(x, y);
    territoryBar.setColor(sf::Color(255,239,229));
    territoryBar.setBackgroundColor(sf::Color(23, 23, 25));
    territoryBar.setFrameColor(sf::Color(23, 23, 25));

    Game::m_main_window.draw(territoryBar);

    // Display power percent
    float powerPercent = (float) m_bot->getPower() / (float) (Game::m_map.getPower() == 0 ? 1 : Game::m_map.getPower());
    powerPercent *= 100.0f;

    y += 30;

    ProgressBar powerBar(powerPercent);
    powerBar.setShowBackgroundAndFrame(true);
    powerBar.setSize({ SCORE_WIDTH - 40.0f, 20.f });
    powerBar.move(x, y);
    powerBar.setColor(sf::Color(111, 177, 207));
    powerBar.setBackgroundColor(sf::Color(23, 23, 25));
    powerBar.setFrameColor(sf::Color(23, 23, 25));

    Game::m_main_window.draw(powerBar);
}
