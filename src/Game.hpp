#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Map.hpp"
#include "Score.hpp"
#include "Bot.hpp"

#define GAME_NAME "Polybasite"

enum GameState {
    STATE_UNINITIALISED,
    STATE_PLAY,
    STATE_REPLAY,
    STATE_PAUSE,
    STATE_FINISH,
    STATE_QUIT,
};

class Game {
public:
    /* Game constant */
    static const unsigned SCREEN_WIDTH = 1024;
    static const unsigned SCREEN_HEIGHT = 650;
    static const unsigned MAX_TURN = 1500;
    static const unsigned SPEED_STEP = 50;
    static char** save_argv;
    static int save_argc;

    static GameState m_state;
    static sf::RenderWindow m_main_window;
    static Map m_map;
    static std::vector<Bot*> m_bots;
    static unsigned m_nb_turn;
    static unsigned m_turn_speed;

    static void start(int argc, char* argv[]);
    static void restart();
    static void quit();
private:
    static void turn();
    static void loop();
    static void displayBotNames();
    static bool hasWinner();
    static void displayWinner();
    static void displayScore();
    static void displayTurn();
};

#endif /* __GAME_HPP__ */
