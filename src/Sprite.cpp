#include "Sprite.h"
#include "Game.h" // Necessário para acessar Game::GetInstance().GetRenderer()
#include <iostream>

Sprite::Sprite() {
    texture = nullptr;
    frameCountW = 1;
    frameCountH = 1;
}

Sprite::Sprite(std::string file, int frameCountW, int frameCountH) 
{
    texture = nullptr;
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;
    Open(file);
}

Sprite::~Sprite() {
    if (texture != nullptr) 
    {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(std::string file) 
{
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    texture = IMG_LoadTexture(renderer, file.c_str());

    if (texture == nullptr) 
    {
        std::cout << "Falha ao carregar textura: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    SetClip(0, 0, GetWidth(), GetHeight());
}

void Sprite::SetClip(int x, int y, int w, int h) 
{
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y, int w, int h) 
{
    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    SDL_Rect dstrect;
    
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = w;
    dstrect.h = h;
    SDL_RenderCopy(renderer, texture, &clipRect, &dstrect);
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

void Sprite::SetFrameCount(int frameCountW, int frameCountH)
{
	this->frameCountW = frameCountW;
	this->frameCountH = frameCountH;
}

void Sprite::SetFrame(int frame)
{
	int frameWidth = GetWidth();
	int frameHeight = GetHeight();
	
	int x = (frame % frameCountW) * frameWidth;
	int y = (frame / frameCountW) * frameHeight;
	
	SetClip(x, y, frameWidth, frameHeight);
}










