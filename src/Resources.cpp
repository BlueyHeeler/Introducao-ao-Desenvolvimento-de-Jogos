#include "Resources.h"
#include "Game.h"
#include <iostream>

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage(std::string file) 
{
    const auto found = imageTable.find(file);
    if (found != imageTable.end()) 
        return found->second;
    SDL_Texture* image = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if (!image) 
    {
        std::cerr << "Erro ao carregar imagem " << file << ": " << IMG_GetError() << '\n';
        return nullptr;
    }
    imageTable.emplace(file, image);
    return image;
}

Mix_Music* Resources::GetMusic(std::string file) 
{
    const auto found = musicTable.find(file);
    if (found != musicTable.end()) 
        return found->second;
    Mix_Music* music = Mix_LoadMUS(file.c_str());
    if (!music) 
    {
        std::cerr << "Erro ao carregar musica " << file << ": " << Mix_GetError() << '\n';
        return nullptr;
    }
    musicTable.emplace(file, music);
    return music;
}

Mix_Chunk* Resources::GetSound(std::string file) 
{
    const auto found = soundTable.find(file);
    if (found != soundTable.end()) 
        return found->second;
    Mix_Chunk* sound = Mix_LoadWAV(file.c_str());
    if (!sound)
    {
        std::cerr << "Erro ao carregar som " << file << ": " << Mix_GetError() << '\n';
        return nullptr;
    }
    soundTable.emplace(file, sound);
    return sound;
}

void Resources::ClearImages() 
{
    for (const auto& entry : imageTable)
    { 
        SDL_DestroyTexture(entry.second);
    }
    imageTable.clear();
}
void Resources::ClearMusics()
{
    Mix_HaltMusic();
    for (const auto& entry : musicTable)
    { 
        Mix_FreeMusic(entry.second);
    }
    musicTable.clear();
}
void Resources::ClearSounds() 
{
    Mix_HaltChannel(-1);
    for (const auto& entry : soundTable)
    { 
        Mix_FreeChunk(entry.second);
    }
    soundTable.clear();
}
