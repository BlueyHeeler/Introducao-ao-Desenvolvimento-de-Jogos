#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H
// include/PlayerController.h
#pragma once
#include "Component.h"

class PlayerController : public Component {
public:
    PlayerController(GameObject& associated);
    ~PlayerController() override;

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
};
#endif // PLAYER_CONTROLLER_H
