#include "Enemy.h"
#include "UIMGR.h"
#include "ObjectMGR.h"
#include "CreateUI.h"

void Enemy::Init()
{
	player = ObjectMGR::GetInstance()->FindObject("Player");
}
void Enemy::Release() {}
void Enemy::Start() {}
void Enemy::Update()
{
	m_dmgCnt--;
	if (m_dmgCnt <= 0)
	{
		static RECT temp, playerRt, myRt;
		myRt =
		{ m_gameObj->Position()->X - m_gameObj->Size()->X / 2,
		m_gameObj->Position()->Y - m_gameObj->Size()->Y / 2 ,
		m_gameObj->Position()->X + m_gameObj->Size()->X / 2 ,
		m_gameObj->Position()->Y + m_gameObj->Size()->Y / 2 };
		playerRt =
		{ player->Position()->X - player->Size()->X / 3,
		player->Position()->Y - player->Size()->Y / 3 ,
		player->Position()->X + player->Size()->X / 3 ,
		player->Position()->Y + player->Size()->Y / 3 };
		if (IntersectRect(&temp, &myRt, &playerRt))
		{
			//µ¥¹ÌÁö
			GameObject* tmp = UIMGR::GetInstance()->FindObject("HPBar");
			if (tmp->GetActive())
			{
				((HPBar*)tmp->GetComponent<HPBar>())->Event(m_dmg * 100);
			}
		}
		m_dmgCnt = 10;
	}
}