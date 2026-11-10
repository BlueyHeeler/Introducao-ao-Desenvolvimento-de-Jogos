// src/PlayerController.cpp
#include "PlayerController.h"
#include "GameObject.h"
#include "Character.h"
#include "InputManager.h"
#include "Camera.h"

PlayerController::PlayerController(GameObject& associated) : Component(associated) {}

PlayerController::~PlayerController() {}

void PlayerController::Start() {}

void PlayerController::Update(float dt) {
    Character* character = static_cast<Character*>(associated.GetComponent("Character"));
    if (!character) {
        return;
    }

    InputManager& input = InputManager::GetInstance();

    if (input.IsKeyDown(SDLK_w)) {
        character->Issue(Character::Command(Character::Command::MOVE, 0.0f, -1.0f));
    }
    if (input.IsKeyDown(SDLK_s)) {
        character->Issue(Character::Command(Character::Command::MOVE, 0.0f, 1.0f));
    }
    if (input.IsKeyDown(SDLK_a)) {
        character->Issue(Character::Command(Character::Command::MOVE, -1.0f, 0.0f));
    }
    if (input.IsKeyDown(SDLK_d)) {
        character->Issue(Character::Command(Character::Command::MOVE, 1.0f, 0.0f));
    }

    if (input.MousePress(LEFT_MOUSE_BUTTON)) {
        float targetX = input.GetMouseX() + Camera::pos.x;
        float targetY = input.GetMouseY() + Camera::pos.y;
        character->Issue(Character::Command(Character::Command::SHOOT, targetX, targetY));
    }
}

void PlayerController::Render() {}

bool PlayerController::Is(std::string type) {
    return type == "PlayerController";
}