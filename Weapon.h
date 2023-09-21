#pragma once
#include "Component.h"
#include "GameObject.h"
#include"Global.h"


class Weapon : public Component
{
protected:
	int m_Damage = 1;
	int m_Speed = 1;
public:
	Weapon(GameObject* gameObj) : Component(gameObj){}

	virtual void Init() abstract;
	virtual void Release() abstract;
	virtual void Start() abstract;
	virtual void Update() abstract;

	int GetDamage() {
		return m_Damage;
	}
	void SetDamage(int Damage) {
		m_Damage = Damage;
	}
	int GetSpeed() {
		return m_Speed;
	}
	void SetSpeed(int Speed) {
		m_Speed = Speed;
	}
	void UpgradeSpeed() {
		m_Speed++;
	}
};