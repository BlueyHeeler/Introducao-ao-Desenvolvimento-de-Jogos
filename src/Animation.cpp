// src/Animation.cpp
#include "Animation.h"

Animation::Animation(int frameStart, int frameEnd, float frameTime, SDL_RendererFlip flip)
    : frameStart(frameStart), frameEnd(frameEnd), frameTime(frameTime), flip(flip) {}