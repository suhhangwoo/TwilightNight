#pragma once
#include"GameObject.h"
#include"Component.h"
#include"Mouse.h"
#include"ObjectMGR.h"


class BtnObject : public Component {
private:
	int m_BtnID;
public:
	BtnObject(GameObject* gameObj, int id);

	void Init() override{}
	void Release() override{}
	void Start() override{}
	void Update() override{}

	int GetBtnID();
	void SetBtnID(int m);

	bool Check(HWND hwnd);
};