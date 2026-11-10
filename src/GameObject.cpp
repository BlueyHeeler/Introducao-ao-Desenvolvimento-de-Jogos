#include "GameObject.h"
#include "Camera.h"

GameObject::GameObject() : started(false), angleDeg(0.0), isDead(false) {}

GameObject::~GameObject() {
    components.clear();
}

void GameObject::Start() {
    for (size_t i = 0; i < components.size(); i++) {
        components[i]->Start();
    }
    started = true;
}

void GameObject::Update(float dt) {
    for (size_t i = 0; i < components.size(); i++) {
        components[i]->Update(dt);
    }
}

void GameObject::Render() {
    for (size_t i = 0; i < components.size(); i++) {
        components[i]->Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component* cpt) {
    components.emplace_back(cpt);
    if (started) {
        cpt->Start();
    }
}

void GameObject::RemoveComponent(Component* cpt) {
    for (auto it = components.begin(); it != components.end(); ++it) {
        if (it->get() == cpt) {
            components.erase(it);
            break;
        }
    }
}

Component* GameObject::GetComponent(std::string type) {
    for (size_t i = 0; i < components.size(); i++) {
        if (components[i]->Is(type)) {
            return components[i].get();
        }
    }
    return nullptr;
}

