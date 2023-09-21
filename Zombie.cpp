#include "Zombie.h"
#include "ObjectMGR.h"
#include "AnimationRender.h"

void Zombie::MoveZombie()
{
	GameObject* player = ObjectMGR::GetInstance()->FindObject("Player");
	float x = Component::m_gameObj->Position()->X;
	float y = Component::m_gameObj->Position()->Y;
	float mx = player->Position()->X;
	float my = player->Position()->Y;
	//목표까지의 거리 d
	float d = sqrt((mx - x) * (mx - x) + (my - y) * (my - y));
	float vx, vy;

	if (d)
	{
		vx = (mx - x) / d * m_spd;
		vy = (my - y) / d * m_spd;
	}
	else
	{
		vx = 0;
		vy = m_spd;
	}

	if (mx > x)
	{
		((AnimationRender*)m_gameObj->GetComponent<AnimationRender>())->SetFlipX(true);
	}
	else
	{
		((AnimationRender*)m_gameObj->GetComponent<AnimationRender>())->SetFlipX(false);
	}

	Component::m_gameObj->Position()->X += vx;
	Component::m_gameObj->Position()->Y += vy;
}