#include"BtnObject.h"

BtnObject::BtnObject(GameObject* gameObj, int id):Component(gameObj), m_BtnID(id)
{
}

int BtnObject::GetBtnID()
{
    return m_BtnID;
}

void BtnObject::SetBtnID(int m)
{
    m_BtnID = m;
}

bool BtnObject::Check(HWND hwnd)
{
	RECT rect;


	GameObject* tmp = ObjectMGR::GetInstance()->FindObject("Player");
	CMouse* mouse = CMouse::GetInstance();

	GetClientRect(hwnd, &rect);

	int mx = (tmp->Position()->X + tmp->Size()->X / 2) - (rect.right / 2);
	int my = (tmp->Position()->Y + tmp->Size()->Y / 2) - (rect.bottom / 2);

	COORD m_mPos = mouse->GetPos();


	int x = m_mPos.X + mx;
	int y = m_mPos.Y + my;
	if (((x > m_gameObj->Position()->X && x < (m_gameObj->Position()->X + m_gameObj->Size()->X)) &&
		(y > m_gameObj->Position()->Y && y < (m_gameObj->Position()->Y + m_gameObj->Size()->Y))))
		return true;
	else {
		KillTimer(hwnd, TIMER_UPDATE);
		return false;
	}
}
