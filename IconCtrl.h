#pragma once
#include "BtnObject.h"
#include "GameObject.h"
#include"ObjectMGR.h"
#include"UIMGR.h"
#include"HPBarController.h"
#include"Weapon.h"
#include"BtnObject.h"
#include"TextRender.h"
#include"Global.h"
#include"SoundCtrl.h"
#include"TimeCtrl.h"
#include"CreateUI.h"


class IconCtrl :
	public Component
{
private:
	HWND m_hWnd;
	HBITMAP icon;
public:
	IconCtrl(GameObject* gameObj, HWND hwnd);

	void SetIcon(HBITMAP hBit) { icon = hBit; }

	void Init() override;
	void Release() override;
	void Start() override;
	void Update() override;

	void Event();
};