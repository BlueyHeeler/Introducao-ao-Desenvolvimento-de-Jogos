#ifndef STATE_H
#define STATE_H

#include "SDL_include.h"
#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"
#include <vector>
#include <memory>

class State 
{
public:
    State();
    ~State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();
    void AddObject(GameObject* go);

private:
	Sprite bg;
    Music music;
    bool quitRequested;
	std::vector<std::unique_ptr<GameObject>> objectArray;
};

#endif // STATE_H
