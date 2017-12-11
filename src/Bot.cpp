#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Game.hpp"
#include "Bot.hpp"
#include "Color.hpp"

Bot::~Bot() {

}

void Bot::draw() const {
    std::cout << "DRAW BOT" << std::endl;

    sf::RectangleShape rectangle(sf::Vector2f(ENTITY_WIDTH, ENTITY_HEIGHT));

    rectangle.setFillColor(::Color::Grey);

    Game::m_main_window.draw(rectangle);
}