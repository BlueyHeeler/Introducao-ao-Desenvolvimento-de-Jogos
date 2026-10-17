#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"
#include <cmath>
#include <stdexcept>

Sprite::Sprite()
    : cameraFollower(false), texture(nullptr), width(0), height(0), frameCountW(1), frameCountH(1),
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

void Sprite::Render(float x, float y, int w, int h)
{
    if (!texture || w <= 0 || h <= 0) 
        return;
    if (!cameraFollower)
    {
        x -= Camera::pos.x;
        y -= Camera::pos.y;
    }
    SDL_Rect destination{static_cast<int>(std::round(x)), static_cast<int>(std::round(y)), w, h};
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
