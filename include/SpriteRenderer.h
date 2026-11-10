#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

// include/SpriteRenderer.h
#pragma once
#include <string>
#include "Component.h"
#include "Sprite.h"

class SpriteRenderer : public Component {
public:
    SpriteRenderer(GameObject& associated);
    SpriteRenderer(GameObject& associated, std::string file, int frameCountW = 1, int frameCountH = 1);
    ~SpriteRenderer() override;

    void Open(std::string file);
    void SetFrameCount(int frameCountW, int frameCountH);
    void SetFrame(int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void SetCameraFollower(bool value);
    void SetScale(float scaleX, float scaleY);

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

private:
    Sprite sprite;
};
#endif
