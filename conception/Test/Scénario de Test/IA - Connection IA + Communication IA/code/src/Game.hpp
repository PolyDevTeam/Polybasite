#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#define GAME_NAME "Polybasite"

enum GameState {
    STATE_UNINITIALISED,
    STATE_PLAY,
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

    static GameState m_state;
    static sf::RenderWindow m_main_window;


    static void start(int argc, char* argv[]);
    static void quit();
private:

};

#endif /* __GAME_HPP__ */
