#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Component.h"
#include "Rect.h"
#include <vector>

class GameObject
{
public:
	GameObject();
	~GameObject();
	void Update(float dt);
	void Render();
	bool IsDead();
	void RequestDelete();
	void AddComponent(Component* cpt);
	void RemoveComponent(Component* cpt);
	template<typename T>
	T* GetComponent(){
		long unsigned int index;
		for(index=0;index<components.size();index++){
			T* component = dynamic_cast<T*>(components[index]);
			if(component != nullptr){
				return component;
			}
		}
		return nullptr;
	}
	
	Rect box;
	
private:
	std::vector<Component*> components;
	bool isDead;
	
};
#endif
