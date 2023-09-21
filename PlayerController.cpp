#include "PlayerController.h"
#include "AnimationRender.h"

PlayerController::PlayerController(GameObject* gameObj, int spd) : Component(gameObj), m_speed(spd)
{
}

void PlayerController::SetSpeed(int spd)
{
	m_speed = spd;
}

DIR PlayerController::GetDir()
{
	return m_dir;
}

void PlayerController::Init()
{
	m_ar = (AnimationRender*)m_gameObj->GetComponent<AnimationRender>();
}

void PlayerController::Release()
{
}

void PlayerController::Start()
{
}

void PlayerController::Update()
{
	bool isMove = false;
	DIR dir = { 0.0,0.0 };
	COORD bitInfo = Game::GetInstance()->GetBgResizeInfo();//CWindowFrame::GetInstance()->GetBuffer()->GetBitmapInfo();
	RECT rect = { 0 };
	GetClientRect(CWindowFrame::GetInstance()->GetHWND(), &rect);

	if (GetAsyncKeyState(VK_LEFT) && (m_gameObj->Position()->X - m_speed) >= (0 + (rect.right / 2)))
	{
		isMove = true;
		m_ar->SetFlipX(false);
		m_ar->Update();
		Component::m_gameObj->Position()->X -= m_speed;
		dir.x -= 1.0;
	}
	if (GetAsyncKeyState(VK_RIGHT) && (m_gameObj->Position()->X + m_speed) <= (bitInfo.X - m_gameObj->Size()->X - (rect.right / 2)))
	{
		isMove = true;
		m_ar->SetFlipX(true);
		m_ar->Update();
		Component::m_gameObj->Position()->X += m_speed;
		dir.x += 1.0;
	}
	if (GetAsyncKeyState(VK_UP) && (m_gameObj->Position()->Y - m_speed) >= (0 + (rect.bottom / 2)))
	{
		isMove = true;
		Component::m_gameObj->Position()->Y -= m_speed;
		dir.y -= 1.0;
	}
	if (GetAsyncKeyState(VK_DOWN) && (m_gameObj->Position()->Y + m_speed) <= (bitInfo.Y - m_gameObj->Size()->Y - (rect.bottom / 2)))
	{
		isMove = true;
		Component::m_gameObj->Position()->Y += m_speed;
		dir.y += 1.0;
	}
	VectorNormalize(&dir);
	m_dir = dir;
	if (isMove)
		m_ar->SetPlay(true);
	else
		m_ar->SetPlay(false);
}
