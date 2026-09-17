#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <string>
#include "Sprite.h"
#include "Component.h"

class GameObject;

class SpriteRenderer : public Component
{
public:
	SpriteRenderer(GameObject& associated);
	SpriteRenderer(GameObject& associated, std::string file, int frameCountW = 1, int frameCountH = 1);
	
	void Open(std::string file); 
	void SetFrameCount(int frameCountW, int frameCountH);
	void Update(float dt) override;
	void Render() override;
	
	void SetFrame(int frame);

private:
	Sprite sprite;
};
#endif
