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
#include "Level.h"

static struct GameData {
    int player1Y = 0;
    int player1X = 0;
    int player2Y = 0;
    int player2X = 0;
    int playerSize;
    int playerNum;
    int gameTime; 
} game_data;

class MyGame {

    private:
        SDL_Rect player1 = { 0, 0, 40, 40 };
        SDL_Rect player2 = { 600, 300, 40, 40 };
        SDL_Window* gameWindow = nullptr;

    public:
        Level* level = nullptr;
        SDL_Texture* monkeyText;
        SDL_Texture* pantsText;
        std::vector<std::string> messages;
        TTF_Font* font = nullptr; 
        TTF_Font* smallFont = nullptr; 
        SDL_Colour textColor = { 255, 255, 255 }; 
        SDL_Surface* textSurface = nullptr; 
        SDL_Texture* textTexture = nullptr; 
        SDL_Rect textRect; 
        int textW, textH; 

        bool monkeyWin = false;
        bool pantsWin = false;
        bool pauseMenu = false;
        bool gameIsOver = false;
       

        void on_receive(std::string message, std::vector<std::string>& args);
        void send(std::string message);
        void init(SDL_Renderer* renderer);
        void input(SDL_Event& event);
        SDL_Rect getPlayerOneRect() { return player1; }
        SDL_Rect getPlayerTwoRect() { return player2; }
        void update();
        void render(SDL_Renderer* renderer);
        void drawUI(SDL_Renderer* renderer);
        void gameOver(SDL_Renderer* renderer);
        void quitGame(); 
        void setGameWindow(SDL_Window* window) { gameWindow = window; }
        SDL_Window* getGameWindow() { return gameWindow; }
};

#endif