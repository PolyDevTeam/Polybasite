#include <iostream>
#include <vector>

#include "Game.hpp"
#include "Map.hpp"

GameState Game::m_state = STATE_UNINITIALISED;
sf::RenderWindow Game::m_main_window;
Map Game::m_map(30, 30);


void Game::start(int argc, char *argv[]) {
    if (Game::m_state != STATE_UNINITIALISED)
        return;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    Game::m_main_window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
                               GAME_NAME,
                               sf::Style::Default,
                               settings);

    Game::m_main_window.setVerticalSyncEnabled(true);

    srand(time(NULL)); // Rand initialisation

    Game::m_state = STATE_INIT;


    while (Game::m_state != STATE_QUIT)
        Game::loop();
}

void Game::quit() {
    Game::m_main_window.close();
    Game::m_state = STATE_QUIT;
}

void Game::loop() {
        sf::Event event;
        while (Game::m_main_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                Game::quit();
        }

        // Clear screen
        Game::m_main_window.clear();

        // Draw map
        Game::m_map.draw();



        Game::m_main_window.display();
        std::this_thread::sleep_for (std::chrono::seconds(3));
        std::cout << " Test Affichage OK " << std::endl;
        Game::quit();
}
