#include "Zombie.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Camera.h"
#include "InputManager.h"

Zombie::Zombie(GameObject& associated)
    : Component(associated), hitpoints(100), hit(false),
      hitSound("Recursos/audio/Hit0.wav"), deathSound("Recursos/audio/Dead.wav") {
    associated.AddComponent(new SpriteRenderer(associated, "Recursos/img/Enemy.png", 3, 2));
    Animator* animator = new Animator(associated);
    associated.AddComponent(animator);
    animator->AddAnimation("walking", Animation(0, 3, 0.15f));
    animator->AddAnimation("hit", Animation(4, 4, 0));
    animator->AddAnimation("dead", Animation(5, 5, 0));
    animator->SetAnimation("walking");
}
void Zombie::Damage(int damage) 
{
    if (hitpoints <= 0 || damage <= 0) 
    	return;
    hitSound.Play(1);
    hitpoints = damage >= hitpoints ? 0 : hitpoints - damage;
    Animator* animator = associated.GetComponent<Animator>();
    
    if (hitpoints == 0) 
    {
        hit = false;
        deathTimer.Restart();
        if (animator) animator->SetAnimation("dead");
        deathSound.Play(1);
    }
    else
    {
        hit = true;
        hitTimer.Restart();
        if (animator) animator->SetAnimation("hit");
    }
}

void Zombie::Update(float dt)
{ 
    hitTimer.Update(dt);
    if (hitpoints <= 0)
    {
        deathTimer.Update(dt);
        if (deathTimer.Get() > 5.0f) associated.RequestDelete();
        return;
    }

    if (hit && hitTimer.Get() >= 0.5f)
    {
        hit = false;
        Animator* animator = associated.GetComponent<Animator>();
        if (animator) animator->SetAnimation("walking");
    }

    const InputManager& input = InputManager::GetInstance();
    if (input.MousePress(LEFT_MOUSE_BUTTON))
    {
        const float mouseX = input.GetMouseX() + Camera::pos.x;
        const float mouseY = input.GetMouseY() + Camera::pos.y;
        const Rect& box = associated.box;
        if (mouseX >= box.x && mouseX < box.x + box.w &&
            mouseY >= box.y && mouseY < box.y + box.h)
        {
            Damage(25);
        }
    }
}

void Zombie::Render() {}
