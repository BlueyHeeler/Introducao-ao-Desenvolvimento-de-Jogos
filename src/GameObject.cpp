#include "GameObject.h"

GameObject::GameObject()
{
	isDead = false;
}

GameObject::~GameObject()
{
	for(int i = components.size() - 1; i >= 0; i--)
	{
		delete components[i];
	}
	
	components.clear();
}

void GameObject::Render()
{
	for(Component* t: components)
	{
		t->Render();
	}
}

void GameObject::Update(float dt)
{
	for(Component* t: components)
	{
		t->Update(dt);
	}
}

bool GameObject::IsDead()
{
	return isDead;
}

void GameObject::RequestDelete()
{
	isDead = true;
}

void GameObject::AddComponent(Component* cpt)
{
	components.push_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt)
{
	for(std::size_t i = 0; i<components.size(); i++)
	{
		if(components[i] == cpt)
			components.erase(components.begin() + i);
	}
}

