#pragma once

class GameObject;

class Component abstract
{
protected:
	GameObject* m_gameObj = nullptr;
public:
	Component(GameObject* gameObj); 
	virtual void Init() abstract;
	virtual void Release() abstract;
	virtual void Start() abstract;
	virtual void Update() abstract;
};

