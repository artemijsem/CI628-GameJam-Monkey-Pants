#ifndef __MY_GAME_H__
#define __MY_GAME_H__

#include <iostream>
#include <vector>
#include <string>

#include "SDL.h"

static struct GameData {
    int player1Y = 0;
    int player1X = 0;
    int player2Y = 0;
    int player2X = 0;
    int playerNum;
    std::string level;
} game_data;

class MyGame {

    private:
        SDL_Rect player1 = { 0, 0, 30, 30 };
        SDL_Rect player2 = { 600, 300, 30, 30 };

    public:
        std::vector<std::string> messages;

        void on_receive(std::string message, std::vector<std::string>& args);
        void send(std::string message);
        void input(SDL_Event& event);
        void update();
        void render(SDL_Renderer* renderer);
};

#endif