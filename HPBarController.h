#pragma once
#include "Component.h"
#include "GameObject.h"
#include"ObjectMGR.h"
#include"UIMGR.h"

class HPBar :public Component{
private:
	//COORD m_Start;
	int m_damage = 0;
	int hp = 500;
	int maxHp = 500;
public:
	HPBar(GameObject* gameObj);


	int GetHP() { return hp; }
	void Init() override;
	void Release() override;
	void Start() override;
	void Update() override;

	void Event(float dmg);
};