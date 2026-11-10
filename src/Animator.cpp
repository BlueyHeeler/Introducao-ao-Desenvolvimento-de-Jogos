// src/Animator.cpp
#include "Animator.h"
#include "GameObject.h"
#include "SpriteRenderer.h"

Animator::Animator(GameObject& associated)
    : Component(associated), frameStart(0), frameEnd(0),
      currentFrame(0), frameTime(0.0f), timeElapsed(0.0f), current("") {}

Animator::~Animator() {}

void Animator::Update(float dt) {
    if (frameTime != 0.0f) {
        timeElapsed += dt;
        if (timeElapsed > frameTime) {
            currentFrame++;
            timeElapsed -= frameTime;
            if (currentFrame > frameEnd) {
                currentFrame = frameStart;
            }
            SpriteRenderer* sr = static_cast<SpriteRenderer*>(associated.GetComponent("SpriteRenderer"));
            if (sr) {
                sr->SetFrame(currentFrame, animations[current].flip);
            }
        }
    }
}

void Animator::Render() {}

bool Animator::Is(std::string type) {
    return type == "Animator";
}

void Animator::SetAnimation(std::string name) {
    if (current == name) {
        return;
    }
    auto it = animations.find(name);
    if (it != animations.end()) {
        frameStart = it->second.frameStart;
        frameEnd = it->second.frameEnd;
        frameTime = it->second.frameTime;
        currentFrame = frameStart;
        timeElapsed = 0.0f;
        current = name;

        SpriteRenderer* sr = static_cast<SpriteRenderer*>(associated.GetComponent("SpriteRenderer"));
        if (sr) {
            sr->SetFrame(currentFrame, it->second.flip);
        }
    }
}

void Animator::AddAnimation(std::string name, Animation anim) {
    animations[name] = anim;
}