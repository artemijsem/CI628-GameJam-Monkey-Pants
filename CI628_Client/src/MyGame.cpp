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
        player3.h = game_data.playerSize;
        player3.w = game_data.playerSize;
        player4.h = game_data.playerSize;
        player4.w = game_data.playerSize;
        

        
    }

    if (cmd == "GAME_DATA") {
        // we should have exactly 6 arguments
        if (args.size() == 8) {
            game_data.player1Y = stoi(args.at(0));
            game_data.player1X = stoi(args.at(1));
            game_data.player2Y = stoi(args.at(2));
            game_data.player2X = stoi(args.at(3));
            game_data.player3Y = stoi(args.at(4));
            game_data.player3X = stoi(args.at(5));
            game_data.player4Y = stoi(args.at(6));
            game_data.player4X = stoi(args.at(7));
            //game_data.ballX = stoi(args.at(4));
            //game_data.ballY = stoi(args.at(5));

            
            
          
        }

    }




    else if (cmd == "SPAWN_BOMB")
    {
        std::cout << "SPAWN BOMB: " << cmd << " " << args.at(0) << " " << args.at(1) << std::endl;
        level->updateMap(stoi(args.at(0)), stoi(args.at(1)), 3);
        
    }

    else if (cmd == "SPAWN_POWERUP")
    {
        level->updateMap(stoi(args.at(0)), stoi(args.at(1)), 5);
    }

    else if (cmd == "POWERUP_PICKED")
    {
        level->updateMap(stoi(args.at(0)), stoi(args.at(1)), 0);
    }

    else if (cmd == "BRICK_DESTROYED")
    {
        // make the map tile with brick to become clear (0)
        level->updateMap(stoi(args.at(0)), stoi(args.at(1)), 0);
    }

    else if (cmd == "BOMB_EXPLODED")
    {
        level->bombExplosion(stoi(args.at(0)), stoi(args.at(1)), stoi(args.at(2)));
        std::cout << "BOMB_EXPLODED : " << cmd << " " << args.at(0) << " " << args.at(1) << " " << args.at(2) << std::endl;
        
        level->clearBombExplosion();
    }

    else if (cmd == "PLAYER_LOST")
    {
        switch (stoi(args.at(0)))
        {
        case 1:
            playerOneAlive = false;
            break;
        case 2:
            playerTwoAlive = false;
            break;
        case 3:
            playerThrAlive = false;
            break;
        case 4:
            playerForAlive = false;
            break;
        default:
            break;
        }
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
        case SDLK_SPACE:
            send(event.type == SDL_KEYDOWN ? "F_DOWN" : "F_UP");
            break;
        case SDLK_z:

            send("CLOSED");
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
    player3.y = game_data.player3Y;
    player3.x = game_data.player3X;
    player4.y = game_data.player4Y;
    player4.x = game_data.player4X;

}

void MyGame::gameOver(SDL_Renderer* renderer)
{
    
    SDL_Surface* monkeyWinImage = IMG_Load("../assets/images/Monkey_Win.png");
    SDL_Surface* pantsWinImage = IMG_Load("../assets/images/Pants_Win.png");
    SDL_Surface* mainGameSurface = SDL_GetWindowSurface(gameWindow);
    


    //if (monkeyWin)
    //{
    //    SDL_BlitSurface(monkeyWinImage, NULL, mainGameSurface, NULL);
    //}

    //if (pantsWin)
    //{
    //    SDL_BlitSurface(pantsWinImage, NULL, mainGameSurface, NULL);
    //}
    //



        
    SDL_UpdateWindowSurface(gameWindow);
    SDL_Delay(5000);
    
  /*  if (monkeyWin)
    {
        SDL_FreeSurface(monkeyWinImage);
    }

    if (pantsWin)
    {
        SDL_FreeSurface(pantsWinImage);
    }*/

    

    
}

void MyGame::init(SDL_Renderer* renderer)
{
    level = new Level(renderer);
    level->LevelTime = SDL_GetTicks();
    level->wall = TextureManager::LoadTexture("../assets/images/wall.png", renderer);
    level->brick = TextureManager::LoadTexture("../assets/images/brick.png", renderer);
    level->bomb = TextureManager::LoadTexture("../assets/images/bomb.png", renderer);
    level->bombExplosionWave = TextureManager::LoadTexture("../assets/images/bombExplosion.png", renderer);
    level->powerUp = TextureManager::LoadTexture("../assets/images/powerup.png", renderer);
    playerOneText = TextureManager::LoadTexture("../assets/images/Player_One.png", renderer);
    playerTwoText = TextureManager::LoadTexture("../assets/images/Player_Two.png", renderer);
    playerThreeText = TextureManager::LoadTexture("../assets/images/Player_Three.png", renderer);
    playerFourText = TextureManager::LoadTexture("../assets/images/Player_Four.png", renderer);
    TTF_Init();

    font = TTF_OpenFont("../assets/fonts/arial.ttf", 72);
    smallFont = TTF_OpenFont("../assets/fonts/arial.ttf", 24);




}

// Comment
void MyGame::render(SDL_Renderer* renderer) {


    level->drawMap(renderer);

    if(playerOneAlive) TextureManager::Draw(renderer, playerOneText, getPlayerOneRect());
    if(playerTwoAlive) TextureManager::Draw(renderer, playerTwoText, getPlayerTwoRect());
    if(playerThrAlive) TextureManager::Draw(renderer, playerThreeText, getPlayerThreeRect());
    if(playerForAlive) TextureManager::Draw(renderer, playerFourText, getPlayerFourRect());

    drawUI(renderer);

    
    //if (monkeyWin) { gameOver(renderer); }
    //if (pantsWin) { gameOver(renderer); }
    /*DrawCircle(renderer, game_data.ballX, game_data.ballY, 5);*/
}

void MyGame::drawUI(SDL_Renderer* renderer) {

    //textSurface = TTF_RenderText_Solid(smallFont, "Game Time", textColor);
    //textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    //SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH);
    //textRect = { 700 - textW/2, 50, textW, textH };
    //SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    //SDL_FreeSurface(textSurface);
    //SDL_DestroyTexture(textTexture);

    ////std::cout << "Drawing UI" << std::endl; 
    //textSurface = TTF_RenderText_Solid(font, std::to_string(game_data.gameTime).c_str(), textColor);
    //textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    //SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH); 
    //textRect = { 675, 100, textW, textH };
    //SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    //SDL_FreeSurface(textSurface); 
    //SDL_DestroyTexture(textTexture); 
}

void MyGame::quitGame() {
    TTF_CloseFont(font); 
    TTF_CloseFont(smallFont); 
    TTF_Quit();
    
}

