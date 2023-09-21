#pragma once
#include "BtnObject.h"
#include "GameObject.h"
#include"ObjectMGR.h"
#include"UIMGR.h"
#include"HPBarController.h"
#include"Weapon.h"
#include"BtnObject.h"
#include"TextRender.h"
#include<time.h>
#include<random>
#include"Global.h"
#include"SoundCtrl.h"
#include"TimeCtrl.h"
#include"CreateUI.h"

enum class SelectNum {
	NONE,
	WEAPON_ADD,
	BULLET_PLUS,
	DAMAGE_UP,
	SPEED_UP,
	END
};



class TextBtn :
    public Component
{
private:
	HWND m_hWnd;
	HBITMAP txt;
	HBITMAP icon;

	Buffer* buf = new Buffer();

	int m_select;
	SelectNum m_effect;
	string weapon;
	Weapon* _weapon;
	TCHAR m_txt[100];
public:
	TextBtn(GameObject* gameObj,HWND hwnd);

	void Init() override;
	void Release() override;
	void Start() override;
	void Update() override;

	HBITMAP GetTxtBit() { return txt; }
	HBITMAP GetIconBit() { return icon; }

	void SetIcon(HBITMAP hBit) { icon = hBit; }
	void SetText(HBITMAP hBit) { txt = hBit; }

	bool WeaponHave();
	void SetSelect();
	void SetEffect();
	void Event();
	void Kind();
	void TextChange(SelectNum select);
	void Effect(SelectNum select);
	void WeaponSetting(int atk,int spd);
	TCHAR* Text(SelectNum select);

};

