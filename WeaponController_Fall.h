#pragma once
#include "Weapon.h"

class WeaponController_Fall : public Weapon
{
private:
	BOOL m_isMovetoLeft;
	typedef struct {
		double x;
		double y;
	}Curve;
	int m_objX;
	int m_objY;
	int m_randPlusX;
	int m_randPlusY;
	double m_CurveT;
public:
	WeaponController_Fall(GameObject* gameObj) : Weapon(gameObj) {}


	Curve MoveAlongCurve(double startX, double startY, double controlX, double controlY, double endX, double endY, double t)
	{
		// 베지어 곡선 계산
		Curve returnCurve;
		returnCurve.x = pow(1 - t, 2) * startX + 2 * t * (1 - t) * controlX + pow(t, 2) * endX;
		returnCurve.y = pow(1 - t, 2) * startY + 2 * t * (1 - t) * controlY + pow(t, 2) * endY;

		return returnCurve;
	}

	void Init() override {
		Reset();
	}

	void Release() override {}
	void Start() override {}
	void Update() override;

	void Reset();


};

