#include "ProfileCtrl.h"

Position::Position(GameObject* gameObj, HWND hWnd) : Component(gameObj), m_hWnd(hWnd) {}

void Position::Init()
{
}

void Position::Release()
{
}

void Position::Start()
{
	m_Start.X = m_gameObj->Position()->X;
	m_Start.Y = m_gameObj->Position()->Y;
}

void Position::Update()
{
	RECT rect;
	GetClientRect(m_hWnd, &rect);

	GameObject* tmp = ObjectMGR::GetInstance()->FindObject("Player");
	m_gameObj->Position()->X = (tmp->Position()->X + tmp->Size()->X / 2) - (rect.right / 2) + m_Start.X;
	m_gameObj->Position()->Y = (tmp->Position()->Y + tmp->Size()->Y / 2) - (rect.bottom / 2) + m_Start.Y;
}
