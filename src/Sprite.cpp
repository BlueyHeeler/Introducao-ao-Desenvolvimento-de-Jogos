#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include <stdexcept>

Sprite::Sprite()
    : texture(nullptr), width(0), height(0), frameCountW(1), frameCountH(1),
      clipRect{0, 0, 0, 0} {}

Sprite::Sprite(std::string file, int frameCountW, int frameCountH) : Sprite() 
{
    SetFrameCount(frameCountW, frameCountH);
    Open(file);
}

Sprite::~Sprite() {}

void Sprite::Open(std::string file)
 {
    texture = Resources::GetImage(file);
    width = height = 0;
    SetClip(0, 0, 0, 0);
    if (!texture) return;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetFrame(0);
}

void Sprite::SetClip(int x, int y, int w, int h) 
{ 
    clipRect = {x, y, w, h};
}

void Sprite::Render(int x, int y, int w, int h) 
{
    if (!texture || w <= 0 || h <= 0) 
        return;
    SDL_Rect destination{x, y, w, h};
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &destination);
}

int Sprite::GetWidth() 
{ 
    return width / frameCountW; 
}

int Sprite::GetHeight() 
{ 
    return height / frameCountH; 
}

bool Sprite::IsOpen() 
{ 
    return texture != nullptr; 
}

void Sprite::SetFrameCount(int columns, int rows) 
{
    if (columns <= 0 || rows <= 0)
        throw std::invalid_argument("Quantidade de frames deve ser positiva.");
    frameCountW = columns;
    frameCountH = rows;
    if (texture) SetFrame(0);
}

void Sprite::SetFrame(int frame)
{
    if (!texture || frame < 0 || frame / frameCountW >= frameCountH) return;
    const int frameWidth = GetWidth();
    const int frameHeight = GetHeight();
    SetClip((frame % frameCountW) * frameWidth,
            (frame / frameCountW) * frameHeight, frameWidth, frameHeight);
}
