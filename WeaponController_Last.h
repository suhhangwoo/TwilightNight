#pragma once
#include "Weapon.h"
class WeaponController_Last : public Weapon
{
private:
	int m_Distance;
	GameObject* m_TargetedEnemy;
	GameObject* m_BeforeTargeted;
public:
	WeaponController_Last(GameObject* gameObj) : Weapon(gameObj) {}

	void Init() override {
	}

	void Release() override {}
	void Start() override {}
	void Update() override;

	void Reset();
	void Targeting();

};

