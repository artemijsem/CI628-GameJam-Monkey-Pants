#include "MyGame.h"

void MyGame::on_receive(std::string cmd, std::vector<std::string>& args) {
    if (cmd == "SETUP")
    {
        game_data.playerNum = stoi(args.at(0));
        std::cout << "Player: " << game_data.playerNum << std::endl;
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

    } else {
        std::cout << "Received: " << cmd << std::endl;
    }
}

void MyGame::send(std::string message) {
    messages.push_back(message);
}

void MyGame::input(SDL_Event& event) {
    //switch (event.key.keysym.sym) {
    //    case SDLK_w:
    //        send(event.type == SDL_KEYDOWN ? "W_DOWN" : "W_UP");
    //        break;
    //    case SDLK_s:
    //        send(event.type == SDL_KEYDOWN ? "S_DOWN" : "S_UP");
    //        break;
    //    case SDLK_a:
    //        send(event.type == SDL_KEYDOWN ? "A_DOWN" : "A_UP");
    //        break;
    //    case SDLK_d:
    //        send(event.type == SDL_KEYDOWN ? "D_DOWN" : "D_UP");
    //        break;
    //}

    if(event.key.keysym.sym == SDLK_w) send(event.type == SDL_KEYDOWN ? "W_DOWN" : "W_UP");
    if(event.key.keysym.sym == SDLK_s) send(event.type == SDL_KEYDOWN ? "S_DOWN" : "S_UP");
    if(event.key.keysym.sym == SDLK_a) send(event.type == SDL_KEYDOWN ? "A_DOWN" : "A_UP");
    if(event.key.keysym.sym == SDLK_d) send(event.type == SDL_KEYDOWN ? "D_DOWN" : "D_UP");


}

void MyGame::update() {
    player1.y = game_data.player1Y;
    player1.x = game_data.player1X;
    player2.y = game_data.player2Y;
    player2.x = game_data.player2X;
}

void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

// Comment
void MyGame::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &player1);

    SDL_RenderDrawRect(renderer, &player2);
    /*DrawCircle(renderer, game_data.ballX, game_data.ballY, 5);*/
}