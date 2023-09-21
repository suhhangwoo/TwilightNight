#pragma once
#include "Component.h"

class Enemy : public Component
{
protected:
	int m_dmg;
	int m_hp;
	int m_spd;
	int m_dmgCnt = 10;

	GameObject* player = nullptr;
public:
	Enemy(GameObject* gameObj) : Component(gameObj) {}

	void Init() override;
	void Release() override;
	void Start() override;
	void Update() override;

	inline int GetDmg() const { return m_dmg; }
	inline void SetDmg(int dmg) { m_dmg = dmg; }
	inline int GetHp() const { return m_hp; }
	inline void SetHp(int hp) { m_hp = hp; }
	inline int GetSpd() const { return m_spd; }
	inline void SetSpd(int spd) { m_spd = spd; }
};