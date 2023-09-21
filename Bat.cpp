#include "Bat.h"
#include "AnimationRender.h"
#include "ObjectMGR.h"
#include "GameObject.h"

void Bat::MoveBat()
{
	Component::m_gameObj->Position()->X += m_vx;
	Component::m_gameObj->Position()->Y += m_vy;
}

void Bat::DeleteBat()
{
	if (!Component::m_gameObj->GetDestroy())
		if (ObjectMGR::GetInstance()->CheckScreenOut(Component::m_gameObj->Position()->X, Component::m_gameObj->Position()->Y))
			Component::m_gameObj->SetDestroy(true);
}