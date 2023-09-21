#include "WeaponController_Shoot.h"

#include "ObjectMGR.h"
#include <cmath>


static int Way_toSave = 6;
void WeaponController_Shoot::Update()
{
	int atk = ((Bullet*)m_gameObj->GetComponent<Bullet>())->GetAtk();
	int spd = ((Bullet*)m_gameObj->GetComponent<Bullet>())->GetSpd();
	GameObject* tmp = ObjectMGR::GetInstance()->FindObject("Player");

	//
	//123
	//4  6
	//689
	//
	if (GetAsyncKeyState(VK_LEFT))
	{
		Way_toSave = 4;
		if (GetAsyncKeyState(VK_UP)) {
			Way_toSave = 1;
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			Way_toSave = 7;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		Way_toSave = 6;
		if (GetAsyncKeyState(VK_UP)) {
			Way_toSave = 3;
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			Way_toSave = 9;
		}
	}
	else if (GetAsyncKeyState(VK_UP)) {
		Way_toSave = 2;
	}
	else if (GetAsyncKeyState(VK_DOWN)) {
		Way_toSave = 8;
	}

	RECT rt;
	GetClientRect(CWindowFrame::GetInstance()->GetHWND(), &rt);

	const double PI = 3.14159265358979323846;
	float diagonalDistance = (spd *2 + 4) * sqrt(2);
	float xDistance = diagonalDistance * cos(PI / 4); 
	float yDistance = diagonalDistance * sin(PI / 4);


	if (m_WaytoMove == 1) {
		m_gameObj->Position()->X -= xDistance;
		m_gameObj->Position()->Y -= yDistance;
		if (m_gameObj->Position()->X <= (tmp->Position()->X - (rt.right / 2))) {
			Reset();
		}
		else if (m_gameObj->Position()->Y <= (tmp->Position()->Y - (rt.bottom / 2))) {
			Reset();
		}
	}
	else if (m_WaytoMove == 2) {
		Component::m_gameObj->Position()->Y -= (spd * 2 + 4);
		if (m_gameObj->Position()->Y <= (tmp->Position()->Y- (rt.bottom / 2))) {
			Reset();
		}
	}
	else if (m_WaytoMove == 3) {
		m_gameObj->Position()->X += xDistance;
		m_gameObj->Position()->Y -= yDistance;
		if (m_gameObj->Position()->X >= (tmp->Position()->X + (rt.right / 2))) {
			Reset();
		}
		else if (m_gameObj->Position()->Y <= (tmp->Position()->Y - (rt.bottom / 2))) {
			Reset();
		}
	}
	else if (m_WaytoMove == 4) {
		Component::m_gameObj->Position()->X -= (spd * 2 + 4);
		if (m_gameObj->Position()->X <= (tmp->Position()->X - (rt.right /2))) {
			Reset();
		}
	}
	else if (m_WaytoMove == 6) {
		Component::m_gameObj->Position()->X += (spd * 2 + 4);
		if (m_gameObj->Position()->X >= (tmp->Position()->X + (rt.right / 2))) {
			Reset();
		}
	}
	else if (m_WaytoMove == 7) {
		m_gameObj->Position()->X -= xDistance;
		m_gameObj->Position()->Y += yDistance;
		if (m_gameObj->Position()->X <= (tmp->Position()->X - (rt.right / 2))) {
			Reset();
		}
		else if (m_gameObj->Position()->Y >= (tmp->Position()->Y + (rt.bottom / 2))) {
			Reset();
		}
	}
	else if (m_WaytoMove == 8) {
		Component::m_gameObj->Position()->Y += (spd * 2 + 4);
		if (m_gameObj->Position()->Y >= (tmp->Position()->Y + (rt.bottom / 2))) {
			Reset();
		}
	}
	else if (m_WaytoMove == 9) {
		m_gameObj->Position()->X += xDistance;
		m_gameObj->Position()->Y += yDistance;
		if (m_gameObj->Position()->X >= (tmp->Position()->X + (rt.right / 2))) {
			Reset();
		}
		else if (m_gameObj->Position()->Y >= (tmp->Position()->Y + (rt.bottom / 2))) {
			Reset();
		}
	}
	else {
		//for Bug
		Reset();
	}
}

void WeaponController_Shoot::Reset() {
	GameObject* tmp = ObjectMGR::GetInstance()->FindObject("Player");

	int xRand = rand() % 60;
	int yRand = rand() % 90;

	m_WaytoMove = Way_toSave;

	m_gameObj->Position()->X = tmp->Position()->X + xRand;
	m_gameObj->Position()->Y = tmp->Position()->Y + 30 + yRand;

}
