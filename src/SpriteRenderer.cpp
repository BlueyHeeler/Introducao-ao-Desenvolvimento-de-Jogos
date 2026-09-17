#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Component.h"

SpriteRenderer::SpriteRenderer(GameObject& associated) : Component(associated) 
{
}

SpriteRenderer::SpriteRenderer(GameObject& associated, std::string file, int frameCountW, int frameCountH) 
    : Component(associated), sprite(file, frameCountW, frameCountH) 
{
    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();
    
    SetFrame(0);
}

void SpriteRenderer::Open(std::string file) 
{
    sprite.Open(file);
    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();
}

void SpriteRenderer::SetFrameCount(int frameCountW, int frameCountH) 
{
    sprite.SetFrameCount(frameCountW, frameCountH);
}

void SpriteRenderer::Update(float dt) 
{
}

void SpriteRenderer::Render() 
{
    sprite.Render(associated.box.x, associated.box.y, associated.box.w, associated.box.h);
}

void SpriteRenderer::SetFrame(int frame) 
{
    sprite.SetFrame(frame);
}
