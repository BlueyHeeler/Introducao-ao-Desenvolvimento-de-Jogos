// src/SpriteRenderer.cpp
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Component.h"

SpriteRenderer::SpriteRenderer(GameObject& associated) : Component(associated) {}

SpriteRenderer::SpriteRenderer(GameObject& associated, std::string file, int frameCountW, int frameCountH)
    : Component(associated), sprite(file, frameCountW, frameCountH) {
    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();
    sprite.SetFrame(0);
}

SpriteRenderer::~SpriteRenderer() {}

void SpriteRenderer::Open(std::string file) {
    sprite.Open(file);
    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();
}

void SpriteRenderer::SetFrameCount(int frameCountW, int frameCountH) {
    sprite.SetFrameCount(frameCountW, frameCountH);
}

void SpriteRenderer::SetFrame(int frame, SDL_RendererFlip flip) {
    sprite.SetFrame(frame);
    sprite.SetFlip(flip);
}

void SpriteRenderer::SetCameraFollower(bool value) {
    sprite.cameraFollower = value;
}

void SpriteRenderer::SetScale(float scaleX, float scaleY) {
    Vec2 oldCenter(associated.box.x + associated.box.w / 2.0f,
                   associated.box.y + associated.box.h / 2.0f);

    sprite.SetScale(scaleX, scaleY);
    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();

    associated.box.x = oldCenter.x - associated.box.w / 2.0f;
    associated.box.y = oldCenter.y - associated.box.h / 2.0f;
}

void SpriteRenderer::Update(float dt) {}

void SpriteRenderer::Render() {
    sprite.Render(static_cast<int>(associated.box.x),
                  static_cast<int>(associated.box.y),
                  sprite.GetWidth(),
                  sprite.GetHeight(),
                  static_cast<float>(associated.angleDeg));
}

bool SpriteRenderer::Is(std::string type) {
    return type == "SpriteRenderer";
}