#include "Timer.h"

Timer::Timer() : time(0.0f) {}
void Timer::Update(float dt) { time += dt; }
void Timer::Restart() { time = 0.0f; }
float Timer::Get() const { return time; }
