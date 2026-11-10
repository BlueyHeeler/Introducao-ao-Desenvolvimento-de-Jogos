// src/Gun.cpp
#include "Gun.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Bullet.h"
#include "Game.h"
#include "State.h"
#include "InputManager.h"
#include "Camera.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Gun::Gun(GameObject& associated, std::weak_ptr<GameObject> character)
    : Component(associated),
      shotSound("Recursos/audio/Range.wav"),
      reloadSound("Recursos/audio/PumpAction.mp3"),
      cooldownState(0),
      character(character),
      angle(0.0f) {
    SpriteRenderer* sr = new SpriteRenderer(associated, "Recursos/img/Gun.png", 3, 2);
    associated.AddComponent(sr);

    Animator* animator = new Animator(associated);
    animator->AddAnimation("idle", Animation(0, 0, 0.0f, SDL_FLIP_NONE));
    animator->AddAnimation("idle_flipped", Animation(0, 0, 0.0f, SDL_FLIP_VERTICAL));
    animator->AddAnimation("reloading", Animation(1, 5, 0.08f, SDL_FLIP_NONE));
    animator->AddAnimation("reloading_flipped", Animation(1, 5, 0.08f, SDL_FLIP_VERTICAL));
    animator->SetAnimation("idle");
    associated.AddComponent(animator);
}

Gun::~Gun() {}

void Gun::Update(float dt) {
    if (character.expired()) {
        associated.RequestDelete();
        return;
    }

    std::shared_ptr<GameObject> charGO = character.lock();
    Animator* animator = static_cast<Animator*>(associated.GetComponent("Animator"));

    // Máquina de estados do cooldown (0: pronta, 1: pós-tiro, 2: recarregando, 3: pós-recarga)
    if (cooldownState != 0) {
        cdTimer.Update(dt);
    }

    bool flipped = (std::cos(angle) < 0.0f);

    switch (cooldownState) {
        case 0: {
            // Opcional: aponta continuamente para o mouse quando pronta, ou mantém o ângulo
            InputManager& input = InputManager::GetInstance();
            Vec2 mousePos(input.GetMouseX() + Camera::pos.x, input.GetMouseY() + Camera::pos.y);
            Vec2 charCenter(charGO->box.x + charGO->box.w / 2.0f, charGO->box.y + charGO->box.h / 2.0f);
            angle = std::atan2(mousePos.y - charCenter.y, mousePos.x - charCenter.x);
            flipped = (std::cos(angle) < 0.0f);
            if (animator) {
                animator->SetAnimation(flipped ? "idle_flipped" : "idle");
            }
            break;
        }
        case 1:
            if (cdTimer.Get() >= 0.25f) {
                cooldownState = 2;
                reloadSound.Play(1);
                cdTimer.Restart();
                if (animator) {
                    animator->SetAnimation(flipped ? "reloading_flipped" : "reloading");
                }
            }
            break;
        case 2:
            if (cdTimer.Get() >= 0.40f) {
                cooldownState = 3;
                cdTimer.Restart();
                if (animator) {
                    animator->SetAnimation(flipped ? "idle_flipped" : "idle");
                }
            }
            break;
        case 3:
            if (cdTimer.Get() >= 0.25f) {
                cooldownState = 0;
                cdTimer.Restart();
            }
            break;
    }

    // Posiciona o centro da arma à frente do centro do personagem na direção do ângulo
    Vec2 charCenter(charGO->box.x + charGO->box.w / 2.0f,
                    charGO->box.y + charGO->box.h / 2.0f);
    float offsetDist = 45.0f;
    Vec2 gunCenter(charCenter.x + offsetDist * std::cos(angle),
                   charCenter.y + offsetDist * std::sin(angle));

    associated.box.x = gunCenter.x - associated.box.w / 2.0f;
    associated.box.y = gunCenter.y - associated.box.h / 2.0f;
    associated.angleDeg = angle * (180.0 / M_PI);
}

void Gun::Render() {}

bool Gun::Is(std::string type) {
    return type == "Gun";
}

void Gun::Shoot(Vec2 target) {
    if (cooldownState == 0 && !character.expired()) {
        std::shared_ptr<GameObject> charGO = character.lock();
        Vec2 charCenter(charGO->box.x + charGO->box.w / 2.0f,
                        charGO->box.y + charGO->box.h / 2.0f);

        angle = std::atan2(target.y - charCenter.y, target.x - charCenter.x);
        shotSound.Play(1);
        cooldownState = 1;
        cdTimer.Restart();

        // Cria o projétil na ponta do cano da arma
        GameObject* bulletGO = new GameObject();
        Bullet* bullet = new Bullet(*bulletGO, angle, 700.0f, 15, 1000.0f);
        bulletGO->AddComponent(bullet);

        Vec2 gunCenter(associated.box.x + associated.box.w / 2.0f,
                       associated.box.y + associated.box.h / 2.0f);
        float muzzleDist = associated.box.w / 2.0f;
        Vec2 muzzlePos(gunCenter.x + muzzleDist * std::cos(angle),
                       gunCenter.y + muzzleDist * std::sin(angle));

        bulletGO->box.x = muzzlePos.x - bulletGO->box.w / 2.0f;
        bulletGO->box.y = muzzlePos.y - bulletGO->box.h / 2.0f;

            Game::GetInstance().GetState().AddObject(bulletGO);
    }
}