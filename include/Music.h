#ifndef MUSIC_H
#define MUSIC_H

#include <string>
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

class Music 
{
public:
    Music();
    Music(std::string file);
    ~Music();
    
    void Play(int times = -1);
    void Stop(int msToStop = 1500);
    
    void Open(std::string file);
    bool IsOpen();

private:
    Mix_Music* music;
};

#endif // MUSIC_H
