#include "WeaponController_Fall.h"

#include "ObjectMGR.h"



void WeaponController_Fall::Update() {
	int atk = ((Bullet*)m_gameObj->GetComponent<Bullet>())->GetAtk();
	int spd = ((Bullet*)m_gameObj->GetComponent<Bullet>())->GetSpd();
	GameObject* tmp = ObjectMGR::GetInstance()->FindObject("Player");

	RECT rt;
	GetClientRect(CWindowFrame::GetInstance()->GetHWND(), &rt);

	double controlX;
	double controlY;
	double endX;

	//playersize 120x160.
	double startX = m_objX;
	double startY = m_objY;
	if (m_isMovetoLeft) {
		controlX = m_objX - m_randPlusX;
		controlY = m_objY - m_randPlusY;
	}
	else {
		controlX = m_objX + m_randPlusX;
		controlY = m_objY - m_randPlusY;
	}

	if (m_isMovetoLeft) {
		endX = m_objX - (m_randPlusX*2);
	}
	else {
		endX = m_objX + (m_randPlusX * 2);
	}
	double endY = tmp->Position()->Y + (rt.bottom/2) + 100;

	Curve myCurve = MoveAlongCurve(startX, startY, controlX, controlY, endX, endY, m_CurveT);
	Component::m_gameObj->Position()->X = myCurve.x;
	Component::m_gameObj->Position()->Y = myCurve.y;

	m_CurveT += (0.008 + (0.002 * spd));
	if (m_CurveT >= 1) {
		Reset();
	}
}

void WeaponController_Fall::Reset() {
	GameObject* tmp = ObjectMGR::GetInstance()->FindObject("Player");

	m_isMovetoLeft = rand() % 2;
	int xRand = rand() % 60;
	int yRand = rand() % 90;
	m_randPlusY = (rand() % 300) + 200;
	m_randPlusX = (rand() % 100) + 100;
	m_gameObj->Position()->X = tmp->Position()->X + xRand;
	m_gameObj->Position()->Y = tmp->Position()->Y + 30 + yRand;

	m_objX = m_gameObj->Position()->X;
	m_objY = m_gameObj->Position()->Y;
	m_CurveT = 0;
}