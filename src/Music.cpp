#include "Music.h"
#include "Resources.h"

Music::Music() : music(nullptr) {}

Music::Music(std::string file) : Music() 
{ 
    Open(file); 
}

Music::~Music() 
{ 
    Stop(0); 
}

void Music::Open(std::string file) 
{
    if (music) 
    	Stop(0);
    music = Resources::GetMusic(file);
}

void Music::Play(int times) 
{
    if (music) 
    	Mix_PlayMusic(music, times);
}

void Music::Stop(int msToStop) 
{
    if (!music) 
    	return;
    if (msToStop <= 0) 
    	Mix_HaltMusic();
    else 
    	Mix_FadeOutMusic(msToStop);
}

bool Music::IsOpen() 
{
    return music != nullptr; 
}
