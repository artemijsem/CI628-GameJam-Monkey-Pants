#include "MyGame.h"
#include "Level.h"
#include "TextureManager.h"

void MyGame::on_receive(std::string cmd, std::vector<std::string>& args) {
    if (cmd == "SETUP")
    {
        std::cout << "Setup information recevied" << std::endl; 
        game_data.playerNum = stoi(args.at(0));
        game_data.playerSize = stoi(args.at(1)); 
        std::cout << "Player Size: " << game_data.playerSize << std::endl;
       
        player1.h = game_data.playerSize; 
        player1.w = game_data.playerSize; 
        player2.h = game_data.playerSize; 
        player2.w = game_data.playerSize;
        
        std::cout << "Player: " << game_data.playerNum << std::endl;
        std::cout << cmd << std::endl;

        
    }

    if (cmd == "GAME_DATA") {
        // we should have exactly 6 arguments
        if (args.size() == 4) {
            game_data.player1Y = stoi(args.at(0));
            game_data.player1X = stoi(args.at(1));
            game_data.player2Y = stoi(args.at(2));
            game_data.player2X = stoi(args.at(3));
            //game_data.ballX = stoi(args.at(4));
            //game_data.ballY = stoi(args.at(5));

            
            
          
        }

    }

     else if (cmd == "BAT1_HIT_BAT2") {
        
        monkeyWin = true;
     }

     else if (cmd == "GAME_TIME_OVER")
    {
        pantsWin = true;
    }
    
    else {
        std::cout << "Received: " << cmd << std::endl;
    }
}

void MyGame::send(std::string message) {
    messages.push_back(message);
}

void MyGame::input(SDL_Event& event) {
    switch (event.key.keysym.sym) {
        case SDLK_w:
            send(event.type == SDL_KEYDOWN ? "W_DOWN" : "W_UP");
            break;
        case SDLK_s:
            send(event.type == SDL_KEYDOWN ? "S_DOWN" : "S_UP");
            break;
        case SDLK_a:
            send(event.type == SDL_KEYDOWN ? "A_DOWN" : "A_UP");
            break;
        case SDLK_d:
            send(event.type == SDL_KEYDOWN ? "D_DOWN" : "D_UP");
            break;
        case SDLK_ESCAPE:
            pauseMenu = true;
            break;
    }

    //if(event.key.keysym.sym == SDLK_w) send(event.type == SDL_KEYDOWN ? "W_DOWN" : "W_UP");
    //if(event.key.keysym.sym == SDLK_s) send(event.type == SDL_KEYDOWN ? "S_DOWN" : "S_UP");
    //if(event.key.keysym.sym == SDLK_a) send(event.type == SDL_KEYDOWN ? "A_DOWN" : "A_UP");
    //if(event.key.keysym.sym == SDLK_d) send(event.type == SDL_KEYDOWN ? "D_DOWN" : "D_UP");


}

void MyGame::update() {
    player1.y = game_data.player1Y;
    player1.x = game_data.player1X;
    player2.y = game_data.player2Y;
    player2.x = game_data.player2X;
}

void MyGame::gameOver(SDL_Renderer* renderer)
{
    
    SDL_Surface* monkeyWinImage = IMG_Load("../assets/images/Monkey_Win.png");
    SDL_Surface* pantsWinImage = IMG_Load("../assets/images/Pants_Win.png");
    SDL_Surface* mainGameSurface = SDL_GetWindowSurface(gameWindow);
    


    if (monkeyWin)
    {
        SDL_BlitSurface(monkeyWinImage, NULL, mainGameSurface, NULL);
    }

    if (pantsWin)
    {
        SDL_BlitSurface(pantsWinImage, NULL, mainGameSurface, NULL);
    }
    



        
    SDL_UpdateWindowSurface(gameWindow);
    SDL_Delay(5000);
    
    if (monkeyWin)
    {
        SDL_FreeSurface(monkeyWinImage);
    }

    if (pantsWin)
    {
        SDL_FreeSurface(pantsWinImage);
    }

    gameIsOver = true;

    
}

void MyGame::init(SDL_Renderer* renderer)
{
    level = new Level(renderer);
    level->wall = TextureManager::LoadTexture("../assets/images/wall.png", renderer);
    level->empty = TextureManager::LoadTexture("../assets/images/ground.png", renderer);
    monkeyText = TextureManager::LoadTexture("../assets/images/Monkey_Char.png", renderer);
    pantsText = TextureManager::LoadTexture("../assets/images/Pants_Char.png", renderer);
}

// Comment
void MyGame::render(SDL_Renderer* renderer) {
    level->drawMap(renderer);


    TextureManager::Draw(renderer, monkeyText, getPlayerOneRect());
    TextureManager::Draw(renderer, pantsText, getPlayerTwoRect());

    if (monkeyWin) { gameOver(renderer); }
    if (pantsWin) { gameOver(renderer); }
    /*DrawCircle(renderer, game_data.ballX, game_data.ballY, 5);*/
}