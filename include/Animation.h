#ifndef ANIMATION_H
#define ANIMATION_H

class Animation
{
public:
	Animation(int frameStart, int frameEnd, float frameTime)
	{
		this->frameStart = frameStart;
		this->frameEnd = frameEnd;
		this->frameTime = frameTime;
	}
	
	int frameStart;
	int frameEnd;
	float frameTime;
};
#endif
