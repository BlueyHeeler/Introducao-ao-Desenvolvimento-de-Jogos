#ifndef ANIMATOR_H
#define ANIMATOR_H

// include/Animator.h
#pragma once
#include <unordered_map>
#include <string>
#include "Component.h"
#include "Animation.h"

class Animator : public Component {
public:
    Animator(GameObject& associated);
    ~Animator() override;

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

    void SetAnimation(std::string name);
    void AddAnimation(std::string name, Animation anim);

private:
    std::unordered_map<std::string, Animation> animations;
    int frameStart;
    int frameEnd;
    int currentFrame;
    float frameTime;
    float timeElapsed;
    std::string current;
};
#endif // ANIMATOR_H
