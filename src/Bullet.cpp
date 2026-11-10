// src/Bullet.cpp
#include "Bullet.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance)
    : Component(associated),
      speed(speed * std::cos(angle), speed * std::sin(angle)),
      distanceLeft(maxDistance),
      damage(damage) {
    SpriteRenderer* sr = new SpriteRenderer(associated, "Recursos/img/Bullet.png");
    sr->SetScale(2.0f, 2.0f);
    associated.AddComponent(sr);

    // Soma 90 graus pois o sprite Bullet.png aponta originalmente para cima
    associated.angleDeg = angle * (180.0 / M_PI) + 90.0;
}

Bullet::~Bullet() {}

void Bullet::Update(float dt) {
    Vec2 step(speed.x * dt, speed.y * dt);
    associated.box.x += step.x;
    associated.box.y += step.y;

    float stepDist = std::sqrt(step.x * step.x + step.y * step.y);
    distanceLeft -= stepDist;

    if (distanceLeft <= 0.0f) {
        associated.RequestDelete();
    }
}

void Bullet::Render() {}

bool Bullet::Is(std::string type) {
    return type == "Bullet";
}

int Bullet::GetDamage() {
    return damage;
}