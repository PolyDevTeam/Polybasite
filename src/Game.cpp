#include <iostream>
#include <map>

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
std::map <unsigned, Bot*> Game::m_bots;

unsigned Game::m_nb_turn = 0;
unsigned Game::m_turn_speed = 200;

char** Game::save_argv;
int Game::save_argc;

void Game::start(int argc, char *argv[]) {
    if (Game::m_state != STATE_UNINITIALISED && Game::m_state != STATE_REPLAY)
        return;

    if(argc == 1)
        throw Error();

    if(argc > (int) MAX_BOT + 1)
        throw Error();

    Game::save_argc = argc;
    Game::save_argv = argv;

    // TODO : Add error message when no bot loaded
    srand(time(NULL)); // Rand initialisation

    LOG << "[PolyBasite] START\n";

    for (int i = 0; i < argc - 1; ++i) {
        unsigned pos_x = rand() % m_map.getWidth();
        unsigned pos_y = rand() % m_map.getHeight();

        Bot* bot = new Bot(argv[i + 1], pos_x, pos_y, i);
        bot->setColor(plb::Color::selectRandomSingle());

        Game::m_bots[i] = bot;
    }

    if(m_state == STATE_UNINITIALISED) {
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
    }

    Game::m_state = STATE_PLAY;

    while (Game::m_state != STATE_QUIT)
        Game::loop();
}

void Game::restart() {
    Game::m_state = STATE_REPLAY;
    Game::m_nb_turn = 0;
    Game::m_turn_speed = 200;

    m_map.clear();

    for(std::map<unsigned, Bot*>::iterator it = m_bots.begin(); it != m_bots.end(); ++it) {
        Bot* bot = it->second;
        bot->stopBot();
    }

    Game::m_bots.clear();
    plb::Color::colorAlreadyPicked.clear();

    start(save_argc, save_argv);
}

void Game::quit() {
    if(Game::m_state != STATE_QUIT) {
        LOG << "[PolyBasite] QUIT\n";
        LOG.close();
        Game::m_main_window.close();
        Game::m_state = STATE_QUIT;

        // TODO : Error generated here
        // TODO : Fix all memory leaks
        for(std::map<unsigned, Bot*>::iterator it = m_bots.begin(); it != m_bots.end(); ++it) {
            Bot* bot = it->second;
            bot->stopBot();
            delete bot;
        }

        m_bots.clear();
    }
}

void Game::loop() {
    while (Game::m_main_window.isOpen()) {
        sf::Event event;
        while (Game::m_main_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                Game::quit();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                m_turn_speed += SPEED_STEP;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                if(m_turn_speed >= SPEED_STEP) {
                    m_turn_speed -= SPEED_STEP;
                }
            }

            if(event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Space) {
                    if(m_state == STATE_PAUSE) {
                        m_state = STATE_PLAY;
                    }
                    else {
                        m_state = STATE_PAUSE;
                    }
                }
                else if(event.key.code == sf::Keyboard::Return) {
                    Game::restart();
                }
            }
        }

        // Clear screen
        Game::m_main_window.clear();

        // Draw turn
        Game::displayTurn();

        // Draw legend progress bar
        Score::drawLegend();

        // Draw bot names
        if(m_state == STATE_PLAY || m_state == STATE_PAUSE)
            Game::displayBotNames();

        // Draw map
        Game::m_map.draw();

        // Draw Scores
        Game::displayScore();

        if(hasWinner()) {
            m_state = STATE_FINISH;
            Game::displayWinner();
        }

        if(Game::m_state == STATE_PLAY)
            Game::turn();

        Game::m_main_window.display();
    }

    Game::quit();
}

void Game::displayBotNames() {
    sf::Font font;
    font.loadFromFile("arial.ttf");

    RichText text(font);

    unsigned i = 0;
    for(std::map<unsigned, Bot*>::iterator it = m_bots.begin(); it != m_bots.end(); ++it) {
        Bot* bot = it->second;
        text << bot->getColor() << bot->getName();

        // TODO : Add some security if bot got a long name
        if(i < Game::m_bots.size() - 1) {
            text << sf::Color::White << " vs ";
        }

        ++i;
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

    // TODO : Remove all eliminated bot
    for(std::map<unsigned, Bot*>::iterator it = m_bots.begin(); it != m_bots.end();) {
        Bot* bot = it->second;

        if (bot->getMinerNumber() == 0) {
            bot->stopBot();
            it = Game::m_bots.erase (it);
        }
        else {
            bot->turn();
            ++it;
        }
    }

    // TODO : Fix one turn logging
    LOG << "[Polybasite] ROUND N°" << m_nb_turn << '\n';

    sf::sleep(sf::milliseconds(m_turn_speed));

    Game::m_nb_turn++;
}

bool Game::hasWinner() {
    if(m_bots.size() <= 1 || m_nb_turn >= Game::MAX_TURN)
        return true;
    else
        return false;
}

void Game::displayWinner() {
    sf::RectangleShape rectangleAlpha(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT - Map::OFFSET_Y));
    rectangleAlpha.setFillColor(sf::Color(128, 133, 142, 95));
    rectangleAlpha.move(0, Map::OFFSET_Y);

    sf::Font font;
    font.loadFromFile("arial.ttf");

    RichText winText(font);

    if(m_bots.size() > 0) {
        Bot* botWin = m_bots.begin()->second;
        for(std::map<unsigned, Bot*>::iterator it = ++m_bots.begin(); it != m_bots.end(); ++it) {
            Bot* bot = it->second;

            if(botWin->getPower() < bot->getPower()) {
                botWin = bot;
            }
            else if(botWin->getPower() == bot->getPower()) {
                unsigned random = rand()%100 + 1;

                if(random > 50) {
                    botWin = bot;
                }
                else if (random == 50) {
                    while(random == 50) {
                        random = rand()%100 + 1;

                        if(random > 50) {
                            botWin = bot;
                        }
                        else {
                            break;
                        }
                    }
                }
            }
        }

        winText << botWin->getColor() << botWin->getName();
        winText << sf::Color::White << " win the fight";

        sf::FloatRect textRect = winText.getLocalBounds();
        winText.setOrigin(textRect.width/2,textRect.height/2);
        winText.setPosition(sf::Vector2f(SCREEN_WIDTH/2, Map::OFFSET_Y/2));
    }
    else { // TODO : Test this case
        winText << "Nobody win the fight";
    }

    Game::m_main_window.draw(rectangleAlpha);
    Game::m_main_window.draw(winText);
}

void Game::displayScore() {
    int i = 0;
    for(std::map<unsigned, Bot*>::iterator it = m_bots.begin(); it != m_bots.end(); ++it) {
        Bot* bot = it->second;
        Score score(i, bot);
        score.draw();
        ++i;
    }
}

void Game::displayTurn() {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "ERROR : FONT NOT FOUND" << std::endl;
    }

    sf::Text turn;
    turn.setFont(font);
    turn.setCharacterSize(18);
    turn.setFillColor(sf::Color::White);
    turn.move(Score::SCORE_OFFSET_X, 50);
    turn.setString("Round #" + std::to_string(Game::m_nb_turn));

    sf::RectangleShape line(sf::Vector2f(Score::SCORE_WIDTH - 10, 2));
    line.move(Score::SCORE_OFFSET_X, Score::SCORE_OFFSET_Y - 2);

    Game::m_main_window.draw(turn);
    Game::m_main_window.draw(line);
}