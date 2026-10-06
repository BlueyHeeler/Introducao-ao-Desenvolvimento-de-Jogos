#include "Zombie.h"
#include "SpriteRenderer.h"
#include "Animator.h"

Zombie::Zombie(GameObject& associated)
    : Component(associated), hitpoints(100), deathSound("Recursos/audio/Dead.wav") {
    associated.AddComponent(new SpriteRenderer(associated, "Recursos/img/Enemy.png", 3, 2));
    Animator* animator = new Animator(associated);
    associated.AddComponent(animator);
    animator->AddAnimation("walking", Animation(0, 3, 10));
    animator->AddAnimation("dead", Animation(5, 5, 0));
    animator->SetAnimation("walking");
}
void Zombie::Damage(int damage) 
{
    // Update continua chamando Damage depois da morte: este teste evita repetir o som.
    if (hitpoints <= 0 || damage <= 0) 
    	return;
    hitpoints = damage >= hitpoints ? 0 : hitpoints - damage;
    
    if (hitpoints == 0) 
    {
        Animator* animator = associated.GetComponent<Animator>();
        if (animator) animator->SetAnimation("dead");
        deathSound.Play(1);
    }
}

void Zombie::Update(float) 
{ 
	Damage(1); 
}

void Zombie::Render() {}
