#pragma once
#include "Weapon.h"

class WeaponController_Bounce : public Weapon
{
private:
	float m_radians;
	void getRandomAngle();
public:
	WeaponController_Bounce(GameObject* gameObj) : Weapon(gameObj) {}

	void Init() override {
		getRandomAngle();
	}

	void Release() override {}
	void Start() override {}

	void Update() override;

	void Reset();
};

