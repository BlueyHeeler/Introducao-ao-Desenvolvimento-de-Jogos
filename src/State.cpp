// src/State.cpp
#include "State.h"
#include "InputManager.h"
#include "Camera.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Zombie.h"
#include "Character.h"
#include "PlayerController.h"
#include <algorithm>

State::State() : quitRequested(false), started(false) {
    // Mapa (TileMap)
    GameObject* bgGO = new GameObject();
    bgGO->box.x = 0;
    bgGO->box.y = 0;
    TileSet* tileSet = new TileSet(64, 64, "Recursos/img/Tileset.png");
    TileMap* tileMap = new TileMap(*bgGO, "Recursos/map/map.txt", tileSet);
    tileMap->SetParallax(0, 0.5f);
    tileMap->SetParallax(1, 1.0f);
    bgGO->AddComponent(tileMap);
    AddObject(bgGO);

    // Personagem Jogável em (1280, 1280) com foco da câmera
    GameObject* playerGO = new GameObject();
    playerGO->box.x = 1280;
    playerGO->box.y = 1280;
    playerGO->AddComponent(new Character(*playerGO, "Recursos/img/Player.png"));
    playerGO->AddComponent(new PlayerController(*playerGO));
    AddObject(playerGO);

    Camera::Follow(playerGO);

    music.Open("Recursos/audio/BGM.wav");
    music.Play();
}

State::~State() {
    objectArray.clear();
}

void State::LoadAssets() {
    // Carregamento prévio de assets caso necessário
}

void State::Start() {
    LoadAssets();
    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Start();
    }
    started = true;
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
    std::shared_ptr<GameObject> ptr(go);
    objectArray.push_back(ptr);
    if (started) {
        ptr->Start();
    }
    return std::weak_ptr<GameObject>(ptr);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
    for (size_t i = 0; i < objectArray.size(); i++) {
        if (objectArray[i].get() == go) {
            return std::weak_ptr<GameObject>(objectArray[i]);
        }
    }
    return std::weak_ptr<GameObject>();
}

void State::Update(float dt) {
    InputManager& input = InputManager::GetInstance();
    Camera::Update(dt);

    if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY)) {
        quitRequested = true;
    }

    if (input.KeyPress(SPACE_KEY)) {
        GameObject* zombieGO = new GameObject();
        zombieGO->box.x = input.GetMouseX() + Camera::pos.x;
        zombieGO->box.y = input.GetMouseY() + Camera::pos.y;
        zombieGO->AddComponent(new Zombie(*zombieGO));
        AddObject(zombieGO);
    }

    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    for (size_t i = 0; i < objectArray.size(); i++) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
            i--;
        }
    }

    // Extra: Y-Sorting para efeito isométrico (mantendo o TileMap sempre ao fundo)
    if (objectArray.size() > 1) {
        std::stable_sort(objectArray.begin(), objectArray.end(),
            [](const std::shared_ptr<GameObject>& a, const std::shared_ptr<GameObject>& b) {
                if (a->GetComponent("TileMap") != nullptr) return true;
                if (b->GetComponent("TileMap") != nullptr) return false;
                return (a->box.y + a->box.h) < (b->box.y + b->box.h);
            });
    }
}

void State::Render() {
    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Render();
    }
}

bool State::QuitRequested() {
    return quitRequested;
}