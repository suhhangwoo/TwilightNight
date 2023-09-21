#pragma once
#include "Weapon.h"

class WeaponController_Shoot : public Weapon
{
private:
	int m_WaytoMove;

public:

	WeaponController_Shoot(GameObject* gameObj) : Weapon(gameObj) {}

	void Init() override {
		Reset();
	}

	void Release() override {}
	void Start() override {
	}

	void Update() override;

	void Reset();


};

