#ifndef BULLET_H
#define BULLET_H
// include/Bullet.h
#pragma once
#include "Component.h"
#include "Vec2.h"

class Bullet : public Component {
public:
    Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance);
    ~Bullet() override;

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

    int GetDamage();

private:
    Vec2 speed;
    float distanceLeft;
    int damage;
};
#endif 