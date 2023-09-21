#include "WeaponController_Round.h"

#include "ObjectMGR.h"


void WeaponController_Round::Update() {
	int atk = ((Bullet*)m_gameObj->GetComponent<Bullet>())->GetAtk();
	int spd = ((Bullet*)m_gameObj->GetComponent<Bullet>())->GetSpd();
	GameObject* tmp = ObjectMGR::GetInstance()->FindObject("Player");

	double controlX;
	double controlY;

	//playersize 120x160.
	double startX = tmp->Position()->X - 80;
	double startY = tmp->Position()->Y + 60;
	if (!m_isReturnCurve) {
		controlX = tmp->Position()->X + 40;
		controlY = tmp->Position()->Y - 200;
	}
	else {
		controlX = tmp->Position()->X + 40;
		controlY = tmp->Position()->Y + 320;
	}
	double endX = tmp->Position()->X + 160;
	double endY = tmp->Position()->Y + 60;

	Curve myCurve = MoveAlongCurve(startX, startY, controlX, controlY, endX, endY, m_CurveT);
	Component::m_gameObj->Position()->X = myCurve.x;
	Component::m_gameObj->Position()->Y = myCurve.y;

	if (!m_isReturnCurve) {
		m_CurveT += (0.01 + (0.002* spd));
		if (m_CurveT >= 1) {
			m_isReturnCurve = TRUE;
		}
	}
	else {
		m_CurveT -= (0.01 + (0.002 * spd));
		if (m_CurveT <= 0) {
			m_isReturnCurve = FALSE;
		}
	}

}