#pragma once
#include"Component.h"

class Bullet : public Component {
private:
	int atk=30;
	int spd=1;
	GameObject* m_BeforeDamaged = nullptr;
public:
	Bullet(GameObject* gameObj) : Component(gameObj){}

	int GetAtk() { return atk; }
	void SetAtk(int m) { atk += m; }
	int GetSpd() { return spd; }
	void SetSpd(int m) { spd += m; }

	void Init() override {
	}

	void Release() override {}
	void Start() override {}

	void Update() override;
};