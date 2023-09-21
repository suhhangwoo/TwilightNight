#pragma once
#include "Component.h"
#include "GameObject.h"
#include"ObjectMGR.h"
#include"UIMGR.h"

class Position:public Component {
private:
	HWND  m_hWnd = NULL;
	COORD m_Start;
public:
	Position(GameObject* gameObj, HWND hWnd);

	void Init() override;
	void Release() override;
	void Start() override;
	void Update() override;
};