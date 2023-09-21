#include"LevelController.h"
#include"Buffer.h"
#include"WindowFrame.h"

void Level::Init()
{
}

void Level::Release()
{
}

void Level::Start()
{
	profile = UIMGR::GetInstance()->FindObject("Profile");
	m_gameObj->Size()->X = 0;
}

void Level::Update()
{
	m_gameObj->Size()->X = m_levelGage;
}

void Level::Event()
{
	m_levelGage += m_upLevel;
	if (m_levelGage >= 500) {
		((SndCtrl*)m_gameObj->GetComponent<SndCtrl>())->PlaySndEffect();
		m_levelGage = 0;
		GameObject* tmp = UIMGR::GetInstance()->FindObject("Level");
		((LevelCtrl*)tmp->GetComponent<LevelCtrl>())->Event();

		list<GameObject*>* uiObj = UIMGR::GetInstance()->List();

		for (list<GameObject*>::iterator itr = uiObj->begin(); itr != uiObj->end(); itr++)
		{
			if ((*itr)->GetTag() == "Icon")
				(*itr)->SetActive(true);
			if ((*itr)->GetTag() == "Text")
				(*itr)->SetActive(true);
		}
		for (list<GameObject*>::iterator itr = uiObj->begin(); itr != uiObj->end(); itr++)
		{
			if ((*itr)->GetTag() == "Test") {
				(*itr)->SetActive(true);
				((TextBtn*)(*itr)->GetComponent<TextBtn>())->SetSelect();
				((TextBtn*)(*itr)->GetComponent<TextBtn>())->Kind();
				((TextBtn*)(*itr)->GetComponent<TextBtn>())->SetEffect();
			}
		}
		
		if (m_upLevel >= 50)
			m_upLevel--;
	}
}

Level::Level(GameObject* gameObj, HWND hWnd) : Component(gameObj), m_hWnd(hWnd) {}
