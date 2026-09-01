#ifndef GAME_H
#define GAME_H

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include <string>
#include <stdio.h>
#include "State.h"

class Game 
{
private:
    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;

    Game(std::string title, int width, int height);

public:
    ~Game();
    
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
    static Game& GetInstance(); 
};

#endif // GAME_H
