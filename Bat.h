#pragma once
#include "Enemy.h"

class Bat : public Enemy
{
private:
	float m_vx;
	float m_vy;
public:
	Bat(GameObject* gameObj, float vx, float vy) : Enemy(gameObj), m_vx(vx), m_vy(vy) { Init(); }

	void MoveBat();
	void DeleteBat();

	void Init() final
	{
		Enemy::Init();
		m_dmg = 20;
		m_hp = 50;
		m_spd = 15;
	}
	void Release() final {}
	void Start() final {}
	void Update() final
	{
		Enemy::Update();
		MoveBat();
		DeleteBat();
	}

	inline float GetVx() const { return m_vx; }
	inline void SetVx(float vx) { m_vx = vx; }
	inline float GetVy() const { return m_vy; }
	inline void SetVy(float vy) { m_vy = vy; }
};