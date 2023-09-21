#include "WeaponController_Last.h"
#include "ObjectMGR.h"

#include <math.h>

static int m_UpdateStack = 0;
void WeaponController_Last::Update() {

	int spd = ((Bullet*)m_gameObj->GetComponent<Bullet>())->GetSpd();

	if (m_UpdateStack > 100) {
		Targeting();
		if (m_TargetedEnemy) {
			m_gameObj->Position()->X = m_TargetedEnemy->Position()->X;
			m_gameObj->Position()->Y = m_TargetedEnemy->Position()->Y;
		}
		m_UpdateStack = 0;
	}
	else {
		m_UpdateStack += spd;
		Reset();
	}

}

void WeaponController_Last::Reset() {
	GameObject* tmp = ObjectMGR::GetInstance()->FindObject("Player");
	RECT rt;
	GetClientRect(CWindowFrame::GetInstance()->GetHWND(), &rt);

	m_gameObj->Position()->X = tmp->Position()->X - rt.right - 1000;
	m_gameObj->Position()->Y = tmp->Position()->Y - rt.bottom - 1000;
	//애니메이션 끄는거 추가 
	//or 그냥 active 끄게.

}

void WeaponController_Last::Targeting() {

	GameObject* tmp = ObjectMGR::GetInstance()->FindObject("Player");
	list<GameObject*>* listTmp = ObjectMGR::GetInstance()->GetObjList();
	bool isColl = false;
	int saveDistance = 999999;

	for (list<GameObject*>::iterator itr = listTmp->begin(); itr != listTmp->end(); itr++)
	{
		if ((*itr)->GetTag() == "Enemy")
		{
			m_Distance = ((tmp->Position()->X) - ((*itr)->Position()->X) * (tmp->Position()->X) - ((*itr)->Position()->X)
				+ (tmp->Position()->Y) - ((*itr)->Position()->Y) * (tmp->Position()->Y) - ((*itr)->Position()->Y));

			if (saveDistance > m_Distance) {
				saveDistance = m_Distance;
				m_TargetedEnemy = (*itr);
			}
		}
	}
	
	if (saveDistance == 999999) {
		m_TargetedEnemy = nullptr;
	}

}