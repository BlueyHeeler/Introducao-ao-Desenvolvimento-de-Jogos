#include "Sound.h"
#include "Resources.h"
#include <iostream>

Sound::Sound() : chunk(nullptr), channel(-1) {}

Sound::Sound(std::string file) : Sound() 
{
     Open(file); 
}

Sound::~Sound() { Stop(); }

void Sound::Open(std::string file) 
{
    Stop();
    chunk = Resources::GetSound(file);
}

bool Sound::IsOpen() 
{ 
    return chunk != nullptr;
}

void Sound::Play(int times) 
{
    if (!chunk || times == 0 || times < -1) 
        return;

    Stop();

    int loops;
    if (times == -1)
        loops = -1;
    else 
        loops = times - 1;

    channel = Mix_PlayChannel(-1, chunk, loops);
    
    if (channel == -1) 
        std::cerr << "Erro ao tocar som: " << Mix_GetError() << '\n';
}

void Sound::Stop()
{
    if (chunk && channel >= 0 && Mix_GetChunk(channel) == chunk)
        Mix_HaltChannel(channel);
    channel = -1;
}
