#include "../include/Game.h"

// Inicializando o ponteiro estático da instância
Game* Game::instance = nullptr;

Game& Game::GetInstance() 
{
    if (instance == nullptr) {
        instance = new Game("Erick Taira - 222011525", 1200, 900); 
    }
    return *instance;
}

Game::Game(std::string title, int width, int height) 
{
    if (instance != nullptr) 
    {
        printf("Erro Lógico: O jogo já foi instanciado!\n");
        return;
    }
    instance = this;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) 
    {
        printf("SDL_Init falhou! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    int imageFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
    if ((IMG_Init(imageFlags) & imageFlags) != imageFlags) 
    {
        printf("IMG_Init falhou! SDL_Error: %s\n", SDL_GetError());
    }

    int mixFlags = MIX_INIT_OGG | MIX_INIT_MP3;
    if ((Mix_Init(mixFlags) & mixFlags) != mixFlags) 
    {
        printf("Mix_Init falhou! SDL_Error: %s\n", SDL_GetError());
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) 
    {
        printf("Mix_OpenAudio falhou! SDL_Error: %s\n", SDL_GetError());
    }
    
    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (window == nullptr) 
    {
        printf("Falha na criação da janela! SDL_Error: %s\n", SDL_GetError());
    } else {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == nullptr) {
            printf("Falha na criação do Renderer! SDL Error: %s\n", SDL_GetError());
        }
    }

    state = new State();
}

Game::~Game() 
{
    delete state;
    
    Mix_CloseAudio();
    Mix_Quit();
    
    IMG_Quit();
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    renderer = nullptr;
    window = nullptr;
    
    SDL_Quit();
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
    while (!state->QuitRequested()) 
    {
        state->Update(0.0f);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }
}
