#ifndef GUN_H
#define GUN_H
// include/Gun.h
#pragma once
#include <memory>
#include "Component.h"
#include "Sound.h"
#include "Timer.h"
#include "Vec2.h"

class Gun : public Component {
public:
    Gun(GameObject& associated, std::weak_ptr<GameObject> character);
    ~Gun() override;

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

    void Shoot(Vec2 target);

private:
    Sound shotSound;
    Sound reloadSound;
    int cooldownState;
    Timer cdTimer;
    std::weak_ptr<GameObject> character;
    float angle;
};
#endif