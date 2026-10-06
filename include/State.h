#ifndef STATE_H
#define STATE_H

#include "Music.h"
#include "GameObject.h"
#include <memory>
#include <vector>

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
    Music music;
    bool quitRequested;
    std::vector<std::unique_ptr<GameObject>> objectArray;
};
#endif
