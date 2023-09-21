#pragma once
#include "Enemy.h"

class Coffin : public Enemy
{
public:
	Coffin(GameObject* gameObj) : Enemy(gameObj) {}

	void Init() final
	{
		Enemy::Init();
		m_dmg = 15;
		m_hp = 300;
		m_spd = 0;
	}
	void Release() final {}
	void Start() final {}
	void Update() final
	{
		
		Enemy::Update();
	}
};