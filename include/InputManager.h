#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#define INCLUDE_SDL
#include "SDL_include.h"
#include <unordered_map>

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define SPACE_KEY SDLK_SPACE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT

class InputManager
{
public:
    static InputManager& GetInstance();
    void Update();

    bool KeyPress(int key) const;
    bool KeyRelease(int key) const;
    bool IsKeyDown(int key) const;
    bool MousePress(int button) const;
    bool MouseRelease(int button) const;
    bool IsMouseDown(int button) const;
    int GetMouseX() const;
    int GetMouseY() const;
    bool QuitRequested() const;

private:
    InputManager();
    ~InputManager() = default;
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

    bool mouseState[6];
    int mouseUpdate[6];
    std::unordered_map<int, bool> keyState;
    std::unordered_map<int, int> keyUpdate;
    bool quitRequested;
    int updateCounter;
    int mouseX;
    int mouseY;
};

#endif
