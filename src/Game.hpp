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
    STATE_INIT,
    STATE_PLAY,
    STATE_PAUSE,
    STATE_QUIT,
};

class Game {
public:
    /* Game constant */
    static const unsigned SCREEN_WIDTH = 1024;
    static const unsigned SCREEN_HEIGHT = 650;

    static GameState m_state;
    static sf::RenderWindow m_main_window;
    static Map m_map;
    static vector<Score*> m_scores;
    static std::vector<Bot> m_bots;

  
    static void start(int argc, char* argv[]);
    static void quit();
private:
    static void loop();
    static void displayBotNames();
};

#endif /* __GAME_HPP__ */
