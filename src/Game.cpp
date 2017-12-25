#include <iostream>

#include "Game.hpp"
#include "Map.hpp"
#include "Score.hpp"

GameState Game::m_state = STATE_UNINITIALISED;
sf::RenderWindow Game::m_main_window;
Map Game::m_map;
vector<Score*> Game::m_scores;
//Score Game::m_score(605, 0);

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

    // TODO : Tempory
    unsigned int a = 42;
    for(int i = 0; i < 5; i++){

        Game::m_scores.push_back(new Score(i, std::to_string(i), &a, sf::Color(200, 120, i*20, 220) ) );
    }

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

        // Draw Scores
        for (unsigned i = 0; i < Game::m_scores.size(); ++i) {
            Game::m_scores[i]->draw();
        }


        Game::m_main_window.display();
    }

    Game::quit();
}
