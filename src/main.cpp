#include "Game.h"
#include <exception>
#include <iostream>

int main(int argc, char** argv) 
{
    Game* game = nullptr;
    try
    {
        game = &Game::GetInstance();
        game->Run();
        delete game;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Erro ao executar o jogo: " << error.what() << '\n';
        delete game;
        return 1;
    }
    return 0;
}
