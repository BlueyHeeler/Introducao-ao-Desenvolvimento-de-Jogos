#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

// include/GameObject.h
#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Component.h"
#include "Rect.h"

class GameObject {
public:
    GameObject();
    ~GameObject();

    void Start();
    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    Component* GetComponent(std::string type);

    Rect box;
    bool started;
    double angleDeg;

private:
    std::vector<std::unique_ptr<Component>> components;
    bool isDead;
};
#endif
