#include"HPBarController.h"
#include"Buffer.h"
#include"WindowFrame.h"

void HPBar::Init()
{
	//m_Start.X = m_gameObj->Position()->X;
	//m_Start.Y = m_gameObj->Position()->Y;
}

void HPBar::Release()
{
}

void HPBar::Start()
{
}

HPBar::HPBar(GameObject* gameObj) : Component(gameObj) {}

void HPBar::Update()
{
	//GameObject* tmp = UIMGR::GetInstance()->FindObject("Profile");
	//m_gameObj->Position()->X = (tmp->Position()->X + tmp->Size()->X) + m_Start.X;
	//m_gameObj->Position()->Y = tmp->Position()->Y + m_Start.Y;
}

void HPBar::Event(float dmg) {
	if (hp > 0) {
		m_gameObj->Size()->X -= ((dmg / 100));
		hp -= (dmg / 100);
		((SndCtrl*)m_gameObj->GetComponent<SndCtrl>())->PlaySndEffect();
	}
	if (hp > maxHp) {
		hp = maxHp;
		m_gameObj->Size()->X += ((dmg / 100));
	}
	if (hp <= 0) {
		Game::GetInstance()->ScreenEnd();
		Game::GetInstance()->GameEnd();
	}
}