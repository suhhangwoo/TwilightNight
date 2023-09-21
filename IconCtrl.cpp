#include "IconCtrl.h"

IconCtrl::IconCtrl(GameObject* gameObj, HWND hwnd):Component(gameObj),m_hWnd(hwnd)
{
}

void IconCtrl::Init()
{
	icon = nullptr;
	m_gameObj->AddComponent(new BitmapRender(m_gameObj, icon, RGB(0, 255, 0)));
}

void IconCtrl::Release()
{
}

void IconCtrl::Start()
{

}

void IconCtrl::Update()
{
}

void IconCtrl::Event()
{
	
	list<GameObject*>* uiObj = UIMGR::GetInstance()->List();

	for (list<GameObject*>::iterator itr = uiObj->begin(); itr != uiObj->end(); itr++)
	{
		if ((*itr)->GetTag() == "Test") {
			if (((BtnObject*)(*itr)->GetComponent<BtnObject>())->GetBtnID() == 
				((BtnObject*)m_gameObj->GetComponent<BtnObject>())->GetBtnID()) {
				icon = ((TextBtn*)(*itr)->GetComponent<TextBtn>())->GetIconBit();
				((BitmapRender*)m_gameObj->GetComponent<BitmapRender>())->ChangeBitmap(icon);
			}
		}

	}
}
