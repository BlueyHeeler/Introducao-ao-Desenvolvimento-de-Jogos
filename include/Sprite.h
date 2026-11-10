#ifndef SPRITE_H
#define SPRITE_H

// include/Sprite.h
#pragma once
#include <string>
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Vec2.h"

class Sprite {
public:
    Sprite();
    Sprite(std::string file, int frameCountW = 1, int frameCountH = 1);
    ~Sprite();

    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y, int w, int h, float angle = 0.0f);
    int GetWidth();
    int GetHeight();
    bool IsOpen();
    void SetFrame(int frame);
    void SetFrameCount(int frameCountW, int frameCountH);

    void SetScale(float scaleX, float scaleY);
    Vec2 GetScale();
    void SetFlip(SDL_RendererFlip flip);

    bool cameraFollower;

private:
    SDL_Texture* texture;
    int width;
    int height;
    int frameCountW;
    int frameCountH;
    SDL_Rect clipRect;
    Vec2 scale;
    SDL_RendererFlip flip;
};

#endif // SPRITE_H
