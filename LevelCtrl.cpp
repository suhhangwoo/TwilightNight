#include "LevelCtrl.h"

LevelCtrl::LevelCtrl(GameObject* gameObj):Component(gameObj)
{
}

void LevelCtrl::Init()
{
}

void LevelCtrl::Release()
{
}

void LevelCtrl::Start()
{
	profile = UIMGR::GetInstance()->FindObject("Profile");
}

void LevelCtrl::Update()
{
}

void LevelCtrl::Event()
{
	m_level++;
}

TCHAR* LevelCtrl::Text()
{
	wsprintf(m_txt, TEXT("%d"), m_level);
	return m_txt;
}
