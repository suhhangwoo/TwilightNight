#pragma once
#include "Component.h"
#include "GameObject.h"
#include"ObjectMGR.h"
#include"UIMGR.h"
#include"TextBtn.h"
#include"SoundCtrl.h"
#include"LevelCtrl.h"

class Level :public Component {
private:
	GameObject* profile;
	HWND  m_hWnd=NULL;
	int m_upLevel = 100;
	int m_levelGage = 0;
	TCHAR m_txt[10];
public:
	Level(GameObject* gameObj, HWND hWnd);

	void Init() override;
	void Release() override;
	void Start() override;
	void Update() override;

	void Event();
};