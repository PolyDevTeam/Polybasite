#include <iostream>
#include <vector>

#include "Game.hpp"
#include "Map.hpp"
#include "Bot.hpp"
#include "Score.hpp"
#include "RichText.hpp"

GameState Game::m_state = STATE_UNINITIALISED;
sf::RenderWindow Game::m_main_window;
Map Game::m_map(30, 30);
std::vector <Bot> Game::m_bots;
vector<Score*> Game::m_scores;

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

    // TODO : Initialise bot whith socket communication
    // TODO : Add logging system after this branch

    srand(time(NULL)); // Rand initialisation

    for (int i = 1; i < argc; ++i) {
        std::cout << "BOT NAME " << argv[i] << std::endl;
        // TODO : Select random color
        // TODO : Add some security to counter two bot at the same position
        unsigned pos_x = rand() % m_map.getWidth();
        unsigned pos_y = rand() % m_map.getHeight();
        Bot bot(argv[i], pos_x, pos_y);
        bot.setColor(sf::Color::Red); // TODO : Tempory need bot color selection
        Game::m_bots.push_back(bot);
    }

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

        // TODO : Add multiple text to center text
        sf::Font font;
        font.loadFromFile("arial.ttf");

        RichText text(font);

        for(unsigned i = 0; i < Game::m_bots.size(); ++i) {
            Bot bot = Game::m_bots[i];
            text << bot.getColor() << bot.getName();

            if(i < Game::m_bots.size() - 1)
                 text << sf::Color::White << " vs ";
        }

        // Draw bots name
        Game::m_main_window.draw(text);

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
