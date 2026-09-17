#include "Animator.h"
#include "GameObject.h"
#include "SpriteRenderer.h"

Animator::Animator(GameObject& associated) : Component(associated)
{
    frameStart = 0;
    frameEnd = 0;
    frameTime = 0;
    currentFrame = 0;
    timeElapsed = 0;
}

void Animator::Update(float dt)
{
    if (frameTime == 0) return;

    timeElapsed ++; 
    
    bool frameChanged = false;

    if (timeElapsed > frameTime)
    {
        currentFrame++;
        timeElapsed -= frameTime;
        frameChanged = true;
    }

    if (currentFrame > frameEnd)
    {
        currentFrame = frameStart;
    }

    if (frameChanged)
    {
        SpriteRenderer* sprite = associated.GetComponent<SpriteRenderer>();
        if (sprite != nullptr)
        {
            sprite->SetFrame(currentFrame);
        }
    }
}

void Animator::Render()
{
}

void Animator::SetAnimation(std::string name)
{
    auto it = animations.find(name);
    
    if (it != animations.end())
    {
        frameStart = it->second.frameStart;
        frameEnd = it->second.frameEnd;
        frameTime = it->second.frameTime;
        
        currentFrame = frameStart;
        timeElapsed = 0;

        SpriteRenderer* sprite = associated.GetComponent<SpriteRenderer>();
        if (sprite != nullptr)
        {
            sprite->SetFrame(currentFrame);
        }
    }
}

void Animator::AddAnimation(std::string name, Animation anim)
{
    if (animations.find(name) == animations.end())
    {
        animations.insert({name, anim});
    }
}
