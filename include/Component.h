#ifndef COMPONENT_H
#define COMPONENT_H

// include/Component.h
#pragma once
#include <string>

class GameObject;

class Component {
public:
    Component(GameObject& associated);
    virtual ~Component();

    virtual void Start();
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual bool Is(std::string type) = 0;

protected:
    GameObject& associated;
};
#endif
