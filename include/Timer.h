#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
    Timer();
    void Update(float dt);
    void Restart();
    float Get() const;

private:
    float time;
};

#endif
