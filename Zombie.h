#pragma once
#include "Enemy.h"


class Zombie : public Enemy
{
public:
	Zombie(GameObject* gameObj) : Enemy(gameObj) { Init(); }

	void MoveZombie();

	void Init() final 
	{
		Enemy::Init();
		m_dmg = 10;
		m_hp = 200;
		m_spd = 2;
	}
	void Release() final {}
	void Start() final {}
	void Update() final 
	{
		MoveZombie();

		Enemy::Update();
	}
};