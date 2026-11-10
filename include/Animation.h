#ifndef ANIMATION_H
#define ANIMATION_H

// include/Animation.h
#pragma once
#define INCLUDE_SDL
#include "SDL_include.h"

class Animation {
public:
    Animation(int frameStart = 0, int frameEnd = 0, float frameTime = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);

    int frameStart;
    int frameEnd;
    float frameTime;
    SDL_RendererFlip flip;
};
#endif
