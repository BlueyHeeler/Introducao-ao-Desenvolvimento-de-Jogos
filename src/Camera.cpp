#include "Camera.h"
#include "Game.h"
#include "GameObject.h"
#include "InputManager.h"
#include <cmath>

Vec2 Camera::pos;
Vec2 Camera::speed;
GameObject* Camera::focus = nullptr;

void Camera::Follow(GameObject* newFocus)
{
    focus = newFocus;
    speed = Vec2();
}

void Camera::Unfollow()
{
    focus = nullptr;
    speed = Vec2();
}

void Camera::OnObjectDestroyed(const GameObject* object)
{
    if (focus == object) Unfollow();
}

void Camera::Update(float dt)
{
    if (focus != nullptr)
    {
        int width = 0, height = 0;
        SDL_GetRendererOutputSize(Game::GetInstance().GetRenderer(), &width, &height);
        pos.x = focus->box.x + focus->box.w / 2.0f - width / 2.0f;
        pos.y = focus->box.y + focus->box.h / 2.0f - height / 2.0f;
        speed = Vec2();
        return;
    }

    const InputManager& input = InputManager::GetInstance();
    speed.x = static_cast<float>(input.IsKeyDown(RIGHT_ARROW_KEY))
            - static_cast<float>(input.IsKeyDown(LEFT_ARROW_KEY));
    speed.y = static_cast<float>(input.IsKeyDown(DOWN_ARROW_KEY))
            - static_cast<float>(input.IsKeyDown(UP_ARROW_KEY));

    // Velocidade em pixels/segundo, igual nas diagonais e nos eixos.
    const float length = std::sqrt(speed.x * speed.x + speed.y * speed.y);
    if (length > 0.0f)
    {
        const float cameraSpeed = 400.0f;
        speed.x = speed.x / length * cameraSpeed;
        speed.y = speed.y / length * cameraSpeed;
    }
    pos.x += speed.x * dt;
    pos.y += speed.y * dt;
}
