#include "InputManager.h"
#include <algorithm>
#include <limits>

InputManager::InputManager()
    : mouseState{}, mouseUpdate{}, quitRequested(false), updateCounter(0),
      mouseX(0), mouseY(0)
{
    std::fill(mouseUpdate, mouseUpdate + 6, -1);
}

InputManager& InputManager::GetInstance()
{
    static InputManager instance;
    return instance;
}

void InputManager::Update()
{
    // Preserva o estado das teclas mesmo quando o contador precisa reiniciar.
    if (updateCounter == std::numeric_limits<int>::max())
    {
        updateCounter = 0;
        keyUpdate.clear();
        std::fill(mouseUpdate, mouseUpdate + 6, -1);
    }
    ++updateCounter;
    quitRequested = false;
    SDL_PumpEvents();
    SDL_GetMouseState(&mouseX, &mouseY);

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            quitRequested = true;
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            if (event.key.repeat != 0) break;
            keyState[event.key.keysym.sym] = event.type == SDL_KEYDOWN;
            keyUpdate[event.key.keysym.sym] = updateCounter;
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        {
            const int button = event.button.button;
            if (button > 0 && button < 6)
            {
                mouseState[button] = event.type == SDL_MOUSEBUTTONDOWN;
                mouseUpdate[button] = updateCounter;
            }
            mouseX = event.button.x;
            mouseY = event.button.y;
            break;
        }
        case SDL_MOUSEMOTION:
            mouseX = event.motion.x;
            mouseY = event.motion.y;
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
            {
                // Evita movimento preso ao soltar uma tecla fora da janela.
                for (auto& key : keyState)
                {
                    if (key.second) keyUpdate[key.first] = updateCounter;
                    key.second = false;
                }
                for (int button = 1; button < 6; ++button)
                {
                    if (mouseState[button]) mouseUpdate[button] = updateCounter;
                    mouseState[button] = false;
                }
            }
            break;
        default:
            break;
        }
    }
}

bool InputManager::KeyPress(int key) const
{
    const auto changed = keyUpdate.find(key);
    return IsKeyDown(key) && changed != keyUpdate.end() && changed->second == updateCounter;
}

bool InputManager::KeyRelease(int key) const
{
    const auto changed = keyUpdate.find(key);
    return !IsKeyDown(key) && changed != keyUpdate.end() && changed->second == updateCounter;
}

bool InputManager::IsKeyDown(int key) const
{
    const auto state = keyState.find(key);
    return state != keyState.end() && state->second;
}

bool InputManager::MousePress(int button) const
{
    return button > 0 && button < 6 && mouseState[button] && mouseUpdate[button] == updateCounter;
}

bool InputManager::MouseRelease(int button) const
{
    return button > 0 && button < 6 && !mouseState[button] && mouseUpdate[button] == updateCounter;
}

bool InputManager::IsMouseDown(int button) const
{
    return button > 0 && button < 6 && mouseState[button];
}

int InputManager::GetMouseX() const { return mouseX; }
int InputManager::GetMouseY() const { return mouseY; }
bool InputManager::QuitRequested() const { return quitRequested; }
