#pragma once
#include "Component.h"
#include "GameObject.h"
#include"ObjectMGR.h"
#include"UIMGR.h"
#include"TextBtn.h"

class LevelCtrl :public Component {
private:
	GameObject* profile;
	int m_level = 1;
	TCHAR m_txt[10];
public:
	LevelCtrl(GameObject* gameObj);

	int GetLevel() { return m_level; }

	void Init() override;
	void Release() override;
	void Start() override;
	void Update() override;

	void Event();

	TCHAR* Text();
};