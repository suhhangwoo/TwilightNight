#include "UIMGR.h"
#include "GameObject.h"
#include "Global.h"

UIMGR* UIMGR::m_Pthis = nullptr;

void UIMGR::Create()
{
	if (!m_Pthis)
	{
		m_Pthis = new UIMGR();
		m_Pthis->m_objList = new list<GameObject*>();
	}
}

UIMGR* UIMGR::GetInstance()
{
	return m_Pthis;
}

void UIMGR::Destroy()
{
	if (m_Pthis)
	{
		for (list<GameObject*>::iterator itr = m_Pthis->m_objList->begin(); itr != m_Pthis->m_objList->end(); itr++)
		{
			delete(*itr);
			(*itr) = nullptr;
		}
		delete m_Pthis->m_objList;
		m_Pthis->m_objList = nullptr;

		delete m_Pthis;
		m_Pthis = nullptr;
	}
}

void UIMGR::AllSetActive(bool active)
{
	for (list<GameObject*>::iterator itr = m_Pthis->m_objList->begin(); itr != m_Pthis->m_objList->end(); itr++)
	{
		if((*itr)->GetTag()!="Test")
			(*itr)->SetActive(active);
	}
}

void UIMGR::DeleteAllObject()
{
	for (list<GameObject*>::iterator itr = m_Pthis->m_objList->begin(); itr != m_Pthis->m_objList->end(); itr++)
	{
		(*itr)->SetDestroy(true);
	}
}

list<GameObject*>* UIMGR::List()
{
	return m_objList;
}

void UIMGR::AddObject(GameObject* obj)
{
	m_objList->push_back(obj);
	obj->Init();
	obj->Start();
}


bool UIMGR::DeleteObject(GameObject* obj)
{
	for (list<GameObject*>::iterator itr = m_objList->begin(); itr != m_objList->end(); itr++)
	{
		if ((*itr) == obj)
		{
			(*itr)->Release();
			delete(*itr);
			(*itr) = nullptr;
			m_objList->erase(itr);
			return true;
		}
	}
	return false;
}

bool UIMGR::DeleteObject(string tag)
{
	for (list<GameObject*>::iterator itr = m_objList->begin(); itr != m_objList->end(); itr++)
	{
		if ((*itr)->GetTag() == tag)
		{
			(*itr)->Release();
			delete(*itr);
			(*itr) = nullptr;
			m_objList->erase(itr);
			return true;
		}
	}
	return false;
}

GameObject* UIMGR::FindObject(string tag)
{
	for (list<GameObject*>::iterator itr = m_objList->begin(); itr != m_objList->end(); itr++)
	{
		if ((*itr)->GetTag() == tag)
		{
			return (*itr);
		}
	}
	return nullptr;
}

void UIMGR::Release()
{
	for (list<GameObject*>::iterator itr = m_objList->begin(); itr != m_objList->end(); itr++)
	{
		(*itr)->Release();
	}
}

void UIMGR::Update()
{

	if (Game::GetInstance()->GetState() != E_GAMESTATE::GAME)
		return;

	for (list<GameObject*>::iterator itr = m_objList->begin(); itr != m_objList->end();)
	{
		(*itr)->Update();
		if (((*itr)->GetDestroy()))
		{
			(*itr)->Release();
			delete(*itr);
			(*itr) = nullptr;
			list<GameObject*>::iterator itrTmp = itr;
			itrTmp++;
			m_objList->erase(itr);
			itr = itrTmp;
		}
		else
			itr++;
	}
}
