#ifndef CHARACTER_H
#define CHARACTER_H

#pragma once
#include <string>
#include <queue>
#include <memory>
#include "Component.h"
#include "Vec2.h"
#include "Timer.h"

class Character : public Component {
public:
    class Command {
    public:
        enum CommandType { MOVE, SHOOT };
        Command(CommandType type, float x, float y) : type(type), pos(x, y) {}

        CommandType type;
        Vec2 pos;
    };

    Character(GameObject& associated, std::string sprite);
    ~Character() override;

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

    void Issue(Command task);

    static Character* player;

private:
    std::weak_ptr<GameObject> gun;
    std::queue<Command> taskQueue;
    Vec2 speed;
    float linearSpeed;
    int hp;
    Timer deathTimer;
    bool facingLeft;
};
#endif // CHARACTER_H