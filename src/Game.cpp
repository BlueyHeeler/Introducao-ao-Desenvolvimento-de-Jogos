#include "Game.h"
#include "Resources.h"
#include <stdexcept>

Game* Game::instance = nullptr;

Game& Game::GetInstance() 
{
    if (instance == nullptr)
        instance = new Game("Erick Taira - 222011525", 1200, 900); 
    return *instance;
}

Game::Game(std::string title, int width, int height)
    : window(nullptr), renderer(nullptr), state(nullptr) 
{
    if (instance) 
    	throw std::logic_error("Game ja foi instanciado.");
    instance = this;
    try {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
            throw std::runtime_error(SDL_GetError());
        const int imageFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
        
        if ((IMG_Init(imageFlags) & imageFlags) != imageFlags)
            throw std::runtime_error(IMG_GetError());
        const int mixFlags = MIX_INIT_OGG | MIX_INIT_MP3;
        
        if ((Mix_Init(mixFlags) & mixFlags) != mixFlags)
            throw std::runtime_error(Mix_GetError());
        
        if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
            throw std::runtime_error(Mix_GetError());
        Mix_AllocateChannels(32);
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED, width, height, 0);
        if (!window) 
        	throw std::runtime_error(SDL_GetError());
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        
        if (!renderer) 
        	throw std::runtime_error(SDL_GetError());
        	
        state = new State();
        
    } catch (...) {
        Resources::ClearSounds();
        Resources::ClearMusics();
        Resources::ClearImages();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        Mix_CloseAudio();
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
        instance = nullptr;
        throw;
    }
}

Game::~Game() 
{
    delete state;
    Resources::ClearSounds();
    Resources::ClearMusics();
    Resources::ClearImages();
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    instance = nullptr;
}

State& Game::GetState() 
{
     return *state; 
}

SDL_Renderer* Game::GetRenderer() 
{ 
    return renderer; 
}

void Game::Run() 
{
    while (state && !state->QuitRequested()) 
    {
        state->Update(0.0f);
        SDL_RenderClear(renderer);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }
    delete state;
    state = nullptr;
    Resources::ClearSounds();
    Resources::ClearMusics();
    Resources::ClearImages();
}
