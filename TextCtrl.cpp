#include "TextCtrl.h"

TextCtrl::TextCtrl(GameObject* gameObj, HWND hwnd):Component(gameObj),m_hWnd(hwnd)
{
}

void TextCtrl::Init()
{
	txt = nullptr;
	m_gameObj->AddComponent(new BitmapRender(m_gameObj, txt, RGB(0, 255, 0)));
}

void TextCtrl::Release()
{
}

void TextCtrl::Start()
{
}

void TextCtrl::Update()
{
}

void TextCtrl::Event()
{
	list<GameObject*>* uiObj = UIMGR::GetInstance()->List();

	for (list<GameObject*>::iterator itr = uiObj->begin(); itr != uiObj->end(); itr++)
	{
		if ((*itr)->GetTag() == "Test") {
			if (((BtnObject*)(*itr)->GetComponent<BtnObject>())->GetBtnID() ==
				((BtnObject*)m_gameObj->GetComponent<BtnObject>())->GetBtnID()) {
				txt = ((TextBtn*)(*itr)->GetComponent<TextBtn>())->GetTxtBit();
				((BitmapRender*)m_gameObj->GetComponent<BitmapRender>())->ChangeBitmap(txt);
			}
		}

	}
}
