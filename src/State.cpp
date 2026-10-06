#include "State.h"
#include "SpriteRenderer.h"
#include "TileMap.h"
#include "Zombie.h"

State::State() : quitRequested(false) {
    LoadAssets();
    music.Play(0);

    // Ordem de desenho: fundo, mapa, inimigos.
    std::unique_ptr<GameObject> background(new GameObject());
    background->AddComponent(new SpriteRenderer(*background, "Recursos/img/Background.png", 1, 1));
    background->box.x = 0;
    background->box.y = 0;
    AddObject(background.release());

    std::unique_ptr<GameObject> map(new GameObject());
    map->box.x = 0;
    map->box.y = 0;
    map->AddComponent(new TileMap(*map, "Recursos/map/map.txt",
        new TileSet(64, 64, "Recursos/img/Tileset.png")));
    AddObject(map.release());

    // Objetos diferentes compartilham Enemy.png e Dead.wav via Resources.
    for (int i = 0; i < 3; ++i) {
        std::unique_ptr<GameObject> enemy(new GameObject());
        enemy->AddComponent(new Zombie(*enemy));
        enemy->box.x = 300.0f + i * 250.0f;
        enemy->box.y = 450.0f;
        AddObject(enemy.release());
    }
}

State::~State()
{ 
	objectArray.clear(); 
}

void State::LoadAssets() 
{ 
	music.Open("Recursos/audio/BGM.wav"); 
}

void State::Update(float dt) 
{
    for (std::size_t i = 0; i < objectArray.size(); ++i) objectArray[i]->Update(dt);
    if (SDL_QuitRequested()) 
    	quitRequested = true;
    // Recalcula begin() a cada remocao: erase invalida iteradores.
    for (std::size_t i = 0; i < objectArray.size();) 
    {
        if (objectArray[i]->IsDead()) 
        	objectArray.erase(objectArray.begin() + i);
        else 
        	++i;
    }
}

void State::Render() 
{
    for (const auto& object : objectArray) object->Render();
}

bool State::QuitRequested() 
{ 
	return quitRequested; 
}

void State::AddObject(GameObject* go) 
{ 
	objectArray.emplace_back(go); 
}


