#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

#include <SFML/Graphics.hpp>


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
    static unsigned m_nb_turn;
    static unsigned m_turn_speed;

    static void start(int argc, char* argv[]);
    static void quit();
private:
    static void turn();
    static void loop();

};

#endif /* __GAME_HPP__ */
