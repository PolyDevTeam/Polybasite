#include <iostream>
#include <vector>

#include "Game.hpp"


GameState Game::m_state = STATE_UNINITIALISED;
sf::RenderWindow Game::m_main_window;

unsigned Game::m_nb_turn = 0;
unsigned Game::m_turn_speed = 200;

void Game::start(int argc, char *argv[]) {
    if (Game::m_state != STATE_UNINITIALISED)
        return;

    srand(time(NULL)); // Rand initialisation

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    Game::m_main_window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
                               GAME_NAME,
                               sf::Style::Default,
                               settings);

    // Centering windows
    sf::VideoMode systemResolution = sf::VideoMode::getDesktopMode();
    Game::m_main_window.setVerticalSyncEnabled(true);
    Game::m_main_window.setPosition(sf::Vector2i((systemResolution.width / 2) - SCREEN_WIDTH/2, (systemResolution.height / 2) - SCREEN_HEIGHT / 2));

    Game::m_state = STATE_PLAY;

    while (Game::m_state != STATE_QUIT)
        Game::loop();
}

void Game::quit() {
    if(Game::m_state != STATE_QUIT) {
        Game::m_main_window.close();
        Game::m_state = STATE_QUIT;

    }
}

void Game::loop() {

    while(m_nb_turn <= 20){
    sf::Event event;
    while (Game::m_main_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            Game::quit();
    }

    // Clear screen
    Game::m_main_window.clear();

    // TODO : Tempory display turn
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "ERROR : FONT NOT FOUND" << std::endl;
    }

    sf::Text turn;
    turn.setFont(font);
    turn.setCharacterSize(32);
    turn.setFillColor(sf::Color::White);
    turn.move(450, 200);
    turn.setString("Turn = " + std::to_string(Game::m_nb_turn));
    Game::m_main_window.draw(turn);

    if(Game::m_state == STATE_PLAY)
        Game::turn();

    Game::m_main_window.display();

}
    std::cout << " Test Affichage OK " << std::endl;
    Game::quit();
}

void Game::turn() {

    // TODO : Fix one turn logging
    std::cout << "Tour numéro " << m_nb_turn << std::endl;
    sf::sleep(sf::milliseconds(m_turn_speed));

    Game::m_nb_turn++;
}
