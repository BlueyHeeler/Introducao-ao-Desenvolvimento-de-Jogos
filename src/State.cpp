#include "../include/State.h"
#include "Zombie.h"

State::State()  : bg(), quitRequested(false)
{
    LoadAssets();
    music.Play(0); 

    GameObject* go_zombie = new GameObject();
    Zombie* zombie_comp = new Zombie(*go_zombie);

    go_zombie->AddComponent(zombie_comp);

    go_zombie->box.x = 600;
    go_zombie->box.y = 450;

    AddObject(go_zombie);
}

State::~State()
{
	objectArray.clear();
}

void State::LoadAssets() 
{
	bg.Open("Recursos/img/Background.png");
    music.Open("Recursos/audio/BGM.wav");
}

void State::Update(float dt) 
{
	for(std::size_t i = 0; i < objectArray.size(); i++)
	{
		objectArray[i]->Update(dt);
	}
    if (SDL_QuitRequested()) 
    {
        quitRequested = true;
    }
    auto begin = objectArray.begin();
    for(std::size_t i = 0; i < objectArray.size(); i++)
    {
    	if(objectArray[i]->IsDead())
    	{
    		objectArray.erase(begin + i);
    		i--;
    	}
    }
}

void State::Render() 
{
	bg.Render(0, 0, bg.GetWidth(), bg.GetHeight());
	for(std::size_t i = 0; i <objectArray.size(); i++)
	{
		objectArray[i]->Render();
	}
}

bool State::QuitRequested() 
{
    return quitRequested;
}

void State::AddObject(GameObject* go)
{
	objectArray.emplace_back(go);
}
