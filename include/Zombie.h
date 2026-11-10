#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Component.h"
#include "GameObject.h"
#include "Sound.h"
#include "Timer.h"

class Zombie : public Component 
{
public:
    Zombie(GameObject& associated);
    void Damage(int damage);
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
private:
    int hitpoints;
    bool hit;
    Timer hitTimer;
    Timer deathTimer;
    Sound hitSound;
    Sound deathSound;
};
#endif
