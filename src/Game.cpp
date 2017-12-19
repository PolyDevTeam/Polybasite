#include <iostream>

#include "Game.hpp"
#include "Map.hpp"
#include "Score.hpp"

GameState Game::m_state = STATE_UNINITIALISED;
sf::RenderWindow Game::m_main_window;
Map Game::m_map;
Score Game::m_score(600, 0);

void Game::start() {
    if (Game::m_state != STATE_UNINITIALISED)
        return;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    Game::m_main_window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
                               GAME_NAME,
                               sf::Style::Default,
                               settings);

    Game::m_main_window.setVerticalSyncEnabled(true);

    Game::m_state = STATE_INIT;

    while (Game::m_state != STATE_QUIT)
        Game::loop();
}

void Game::quit() {
    Game::m_main_window.close();
    Game::m_state = STATE_QUIT;
}

void Game::loop() {
    while (Game::m_main_window.isOpen()) {
        sf::Event event;
        while (Game::m_main_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                Game::quit();
        }

        // Clear screen
        Game::m_main_window.clear();

        // Draw map
        Game::m_map.draw();
        Game::m_score.draw();

        Game::m_main_window.display();
    }

    Game::quit();
}
