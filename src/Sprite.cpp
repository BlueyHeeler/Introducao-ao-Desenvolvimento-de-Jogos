// src/Sprite.cpp
#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"

Sprite::Sprite()
    : cameraFollower(false), texture(nullptr), width(0), height(0),
      frameCountW(1), frameCountH(1), scale(1.0f, 1.0f), flip(SDL_FLIP_NONE) {}

Sprite::Sprite(std::string file, int frameCountW, int frameCountH)
    : cameraFollower(false), texture(nullptr), width(0), height(0),
      frameCountW(frameCountW), frameCountH(frameCountH), scale(1.0f, 1.0f), flip(SDL_FLIP_NONE) {
    Open(file);
}

Sprite::~Sprite() {}

void Sprite::Open(std::string file) {
    texture = Resources::GetImage(file);
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClip(0, 0, width / frameCountW, height / frameCountH);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::SetFrame(int frame) {
    int frameW = width / frameCountW;
    int frameH = height / frameCountH;
    int col = frame % frameCountW;
    int row = frame / frameCountW;
    SetClip(col * frameW, row * frameH, frameW, frameH);
}

void Sprite::SetFrameCount(int frameCountW, int frameCountH) {
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;
}

void Sprite::SetScale(float scaleX, float scaleY) {
    if (scaleX != 0.0f) scale.x = scaleX;
    if (scaleY != 0.0f) scale.y = scaleY;
}

Vec2 Sprite::GetScale() {
    return scale;
}

void Sprite::SetFlip(SDL_RendererFlip flip) {
    this->flip = flip;
}

int Sprite::GetWidth() {
    return static_cast<int>((width / frameCountW) * scale.x);
}

int Sprite::GetHeight() {
    return static_cast<int>((height / frameCountH) * scale.y);
}

void Sprite::Render(int x, int y, int w, int h, float angle) {
    SDL_Rect dstRect;
    dstRect.x = cameraFollower ? x : static_cast<int>(x - Camera::pos.x);
    dstRect.y = cameraFollower ? y : static_cast<int>(y - Camera::pos.y);
    dstRect.w = w;
    dstRect.h = h;

    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, angle, nullptr, flip);
}

bool Sprite::IsOpen() {
    return texture != nullptr;
}