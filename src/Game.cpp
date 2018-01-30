#include <iostream>
#include <vector>

#include "Game.hpp"
#include "Log.hpp"
#include "Map.hpp"
#include "Bot.hpp"
#include "Score.hpp"
#include "RichText.hpp"
#include "Socket.hpp"
#include "BlackHole.hpp"
#include "Error.hpp"

GameState Game::m_state = STATE_UNINITIALISED;
sf::RenderWindow Game::m_main_window;
Map Game::m_map(30, 30);
std::vector <Bot*> Game::m_bots;
vector<Score*> Game::m_scores;

unsigned Game::m_nb_turn = 0;
unsigned Game::m_turn_speed = 200;

void Game::start(int argc, char *argv[]) {
    if (Game::m_state != STATE_UNINITIALISED)
        return;

    if(argc == 1)
        throw Error();

    // TODO : Add error message when no bot loaded
    // TODO : If only one bot remaining => He winning the match
    srand(time(NULL)); // Rand initialisation

    LOG << "[PolyBasite] START\n";

    for (int i = 1; i < argc; ++i) {
//       int i = 1;
        unsigned pos_x = rand() % m_map.getWidth();
        unsigned pos_y = rand() % m_map.getHeight();

        Bot* bot = new Bot(argv[i], pos_x, pos_y, i - 1);
        bot->setColor(plb::Color::selectRandomSingle());

        Game::m_bots.push_back(bot);
    }

    // Load sprite
    if(BlackHole::m_texture.loadFromFile("black_hole.png")) {
        // TODO : Make an error
    }

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
    if(Game::m_state != STATE_QUIT) {
        LOG << "[PolyBasite] QUIT\n";
        LOG.close();
        Game::m_main_window.close();
        Game::m_state = STATE_QUIT;

        // TODO : Error generated here
        // TODO : Fix all memory leaks
//        for(Bot* bot : Game::m_bots)
//            delete bot;
    }
}

void Game::loop() {
    while (Game::m_main_window.isOpen()) {
        sf::Event event;
        while (Game::m_main_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                Game::quit();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                m_turn_speed += 50;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                if(m_turn_speed >= 50) {
                    m_turn_speed -= 50;
                }
            }
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
        turn.setCharacterSize(18);
        turn.setFillColor(sf::Color::White);
        turn.move(605, 50);
        turn.setString("Turn = " + std::to_string(Game::m_nb_turn));
        Game::m_main_window.draw(turn);

        // Draw bot names
        Game::displayBotNames();

        // Draw map
        Game::m_map.draw();

        // Draw Scores
        for (unsigned i = 0; i < Game::m_scores.size(); ++i) {
            Game::m_scores[i]->draw();
        }

        Game::turn();

        Game::m_main_window.display();
    }

    Game::quit();
}

void Game::displayBotNames() {
    sf::Font font;
    font.loadFromFile("arial.ttf");

    RichText text(font);

    for(unsigned i = 0; i < Game::m_bots.size(); ++i) {
        Bot* bot = Game::m_bots[i];
        text << bot->getColor() << bot->getName();

        // TODO : Add some security if bot got a long name
        if(i < Game::m_bots.size() - 1)
            text << sf::Color::White << " vs ";
    }

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.width/2,textRect.height/2);
    text.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f, Map::OFFSET_Y/2));

    // Draw bots name
    Game::m_main_window.draw(text);
}

void Game::turn() {
    // Rotate black hole sprite
    BlackHole::m_rotation = ((BlackHole::m_rotation + 90) % 360);

    for(Bot* bot : Game::m_bots)
        bot->turn();

    // TODO : Fix one turn logging
    LOG << "[Polybasite] TURN N°" << m_nb_turn << '\n';

    sf::sleep(sf::milliseconds(m_turn_speed));

    Game::m_nb_turn++;
}