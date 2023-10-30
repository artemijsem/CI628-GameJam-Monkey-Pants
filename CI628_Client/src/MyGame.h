#ifndef __MY_GAME_H__
#define __MY_GAME_H__

#include "SDL_net.h"
#include <SDL.h>
#include<SDL_Image.h>
#include<SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <string>

#include "SDL.h"

static struct GameData {
    int player1Y = 0;
    int player1X = 0;
    int player2Y = 0;
    int player2X = 0;
    int playerSize = 20;
    int playerNum;
} game_data;

class MyGame {

    private:
        SDL_Rect player1 = { 0, 0, game_data.playerSize, game_data.playerSize };
        SDL_Rect player2 = { 600, 300, game_data.playerSize, game_data.playerSize };

    public:
        std::vector<std::string> messages;
       

        void on_receive(std::string message, std::vector<std::string>& args);
        void send(std::string message);
        void input(SDL_Event& event);
        void update();
        void render(SDL_Renderer* renderer);
};

#endif