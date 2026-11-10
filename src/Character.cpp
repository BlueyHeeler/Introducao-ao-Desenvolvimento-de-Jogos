// src/Character.cpp
#include "Character.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Gun.h"
#include "Game.h"
#include "State.h"

Character* Character::player = nullptr;

Character::Character(GameObject& associated, std::string sprite)
    : Component(associated), speed(0.0f, 0.0f), linearSpeed(200.0f), hp(100), facingLeft(false) {
    if (player == nullptr) {
        player = this;
    }

    SpriteRenderer* sr = new SpriteRenderer(associated, sprite, 3, 4);
    associated.AddComponent(sr);

    Animator* animator = new Animator(associated);
    animator->AddAnimation("walking", Animation(0, 5, 0.1f, SDL_FLIP_NONE));
    animator->AddAnimation("walking_left", Animation(0, 5, 0.1f, SDL_FLIP_HORIZONTAL));
    animator->AddAnimation("idle", Animation(6, 9, 0.2f, SDL_FLIP_NONE));
    animator->AddAnimation("idle_left", Animation(6, 9, 0.2f, SDL_FLIP_HORIZONTAL));
    animator->AddAnimation("dead", Animation(10, 11, 0.5f, SDL_FLIP_NONE));
    animator->SetAnimation("idle");
    associated.AddComponent(animator);
}

Character::~Character() {
    if (player == this) {
        player = nullptr;
    }
}

void Character::Start() {
    GameObject* gunGO = new GameObject();
    State& state = Game::GetInstance().GetState();
    gunGO->AddComponent(new Gun(*gunGO, state.GetObjectPtr(&associated)));
    gun = state.AddObject(gunGO);
}

void Character::Update(float dt) {
    Animator* animator = static_cast<Animator*>(associated.GetComponent("Animator"));
    speed = Vec2(0.0f, 0.0f);
    bool moved = false;

    while (!taskQueue.empty()) {
        Command task = taskQueue.front();
        taskQueue.pop();

        if (task.type == Command::MOVE && hp > 0) {
            speed = speed + task.pos;
            moved = true;
        } else if (task.type == Command::SHOOT && hp > 0) {
            if (!gun.expired()) {
                Gun* gunComp = static_cast<Gun*>(gun.lock()->GetComponent("Gun"));
                if (gunComp) {
                    gunComp->Shoot(task.pos);
                }
            }
        }
    }

    if (hp <= 0) {
        if (animator) {
            animator->SetAnimation("dead");
        }
        deathTimer.Update(dt);
        if (deathTimer.Get() > 3.0f) {
            associated.RequestDelete();
        }
        return;
    }

    if (moved && (speed.x != 0.0f || speed.y != 0.0f)) {
        // Normaliza o vetor direção e multiplica por linearSpeed para manter velocidade constante
        float mag = std::sqrt(speed.x * speed.x + speed.y * speed.y);
        speed = Vec2((speed.x / mag) * linearSpeed, (speed.y / mag) * linearSpeed);

        associated.box.x += speed.x * dt;
        associated.box.y += speed.y * dt;

        if (speed.x < 0.0f) {
            facingLeft = true;
        } else if (speed.x > 0.0f) {
            facingLeft = false;
        }

        if (animator) {
            animator->SetAnimation(facingLeft ? "walking_left" : "walking");
        }
    } else {
        if (animator) {
            animator->SetAnimation(facingLeft ? "idle_left" : "idle");
        }
    }
}

void Character::Render() {}

bool Character::Is(std::string type) {
    return type == "Character";
}

void Character::Issue(Command task) {
    taskQueue.push(task);
}