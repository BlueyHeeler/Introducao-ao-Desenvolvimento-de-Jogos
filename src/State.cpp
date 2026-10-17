#include "State.h"
#include "SpriteRenderer.h"
#include "TileMap.h"
#include "Zombie.h"
#include "Camera.h"
#include "InputManager.h"

State::State() : quitRequested(false) {
    Camera::Unfollow();
    Camera::pos = Vec2();
    LoadAssets();
    music.Play(0);

    // Fundo fixo na tela; estrelas, terreno e zombies nessa ordem.
    std::unique_ptr<GameObject> background(new GameObject());
    SpriteRenderer* backgroundSprite = new SpriteRenderer(*background, "Recursos/img/Background.png", 1, 1);
    backgroundSprite->SetCameraFollower(true);
    background->AddComponent(backgroundSprite);
    background->box.x = 0;
    background->box.y = 0;
    AddObject(background.release());

    std::unique_ptr<GameObject> map(new GameObject());
    map->box.x = 0;
    map->box.y = 0;
    TileMap* tileMap = new TileMap(*map, "Recursos/map/map.txt",
        new TileSet(64, 64, "Recursos/img/Tileset.png"));
    map->AddComponent(tileMap);
    if (tileMap->GetDepth() > 1)
        tileMap->SetParallax(0, 0.5f);
    AddObject(map.release());
}

State::~State()
{ 
	Camera::Unfollow();
	objectArray.clear(); 
}

void State::LoadAssets() 
{ 
	music.Open("Recursos/audio/BGM.wav"); 
}

void State::Update(float dt) 
{
    const InputManager& input = InputManager::GetInstance();
    if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY))
    {
        quitRequested = true;
        return;
    }

    Camera::Update(dt);
    if (input.KeyPress(SPACE_KEY))
    {
        std::unique_ptr<GameObject> enemy(new GameObject());
        enemy->AddComponent(new Zombie(*enemy));
        // Centro do zombie sob o cursor, convertendo tela para mundo.
        enemy->box.x = input.GetMouseX() + Camera::pos.x - enemy->box.w / 2.0f;
        enemy->box.y = input.GetMouseY() + Camera::pos.y - enemy->box.h / 2.0f;
        AddObject(enemy.release());
    }

    for (std::size_t i = 0; i < objectArray.size(); ++i) objectArray[i]->Update(dt);
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
    // Neste mapa, camada 0 = estrelas e camada 1 = terreno/agua.
    // Ambas ficam atras dos zombies; desenhar o terreno depois os ocultaria.
    for (const auto& object : objectArray)
    {
        TileMap* map = object->GetComponent<TileMap>();
        if (map)
        {
            for (int layer = 0; layer < map->GetDepth(); ++layer) map->RenderLayer(layer);
        }
        else
            object->Render();
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


