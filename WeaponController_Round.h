#pragma once
#include "Weapon.h"

#include <math.h>
class WeaponController_Round : public Weapon
{
private:
	typedef struct {
		double x;
		double y;
	}Curve;

	double m_CurveT;
	BOOL m_isReturnCurve;
public:

	WeaponController_Round(GameObject* gameObj) : Weapon(gameObj) {}


	Curve MoveAlongCurve(double startX, double startY, double controlX, double controlY, double endX, double endY, double t)
	{
		// 베지어 곡선 계산
		Curve returnCurve;
		returnCurve.x = pow(1 - t, 2) * startX + 2 * t * (1 - t) * controlX + pow(t, 2) * endX;
		returnCurve.y = pow(1 - t, 2) * startY + 2 * t * (1 - t) * controlY + pow(t, 2) * endY;

		return returnCurve;
	}

	void Init() override {
		m_CurveT = 0;
		m_isReturnCurve = FALSE;
	}

	void Release() override {}
	void Start() override {}
	void Update() override;


};

