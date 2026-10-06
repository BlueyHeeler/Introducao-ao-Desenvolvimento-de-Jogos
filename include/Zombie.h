#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Component.h"
#include "GameObject.h"
#include "Sound.h"

class Zombie : public Component 
{
public:
    Zombie(GameObject& associated);
    void Damage(int damage);
    void Update(float dt) override;
    void Render() override;
private:
    int hitpoints;
    Sound deathSound;
};
#endif
