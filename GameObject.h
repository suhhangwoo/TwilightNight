#pragma once
#include <list>
#include "Component.h"
#include <Windows.h>
#include <string>
#include <typeinfo>

using namespace std;

class GameObject
{
protected:
	bool m_isDestroy;
	bool m_setActive = true;
	string m_tag = "";
	COORD m_position = { 0 };
	COORD m_size = { 0 };
	list<Component*>* m_listComponent = nullptr;
public:
	GameObject() :m_isDestroy(false) { m_listComponent = new list<Component*>(); m_isDestroy = false; }
	virtual ~GameObject() {}

	COORD* Position() { return &m_position; }
	COORD* Size() { return &m_size; }

	template <typename T>
	Component* GetComponent()
	{
		for (list<Component*>::iterator itr = m_listComponent->begin(); itr != m_listComponent->end(); itr++)
		{
			if (typeid(**itr) == typeid(T))
			{
				return *itr;
			}
		}
		return nullptr;
	}
	void SetDestroy(bool destroy) { m_isDestroy = destroy; }
	bool GetDestroy() { return m_isDestroy; }
	void SetTag(string tag) { m_tag = tag; }
	string GetTag() { return m_tag; }
	void SetActive(bool isActive) { m_setActive = isActive; }
	bool GetActive() { return m_setActive; }

	//new 해서 생성해서 넣고, 직접 할당 해제하지 말 것
	void AddComponent(Component* component)
	{
		if (component)
		{
			m_listComponent->push_back(component);
		}
	}

	void DeleteComponent(Component* component)
	{
		for (list<Component*>::iterator itr = m_listComponent->begin(); itr != m_listComponent->end(); itr++)
		{
			if ((*itr) == component)
			{
				(*itr)->Release();
				delete(*itr);
				(*itr) = nullptr;
				m_listComponent->erase(itr);
				return;
			}
		}
	}

	void Init()
	{
		m_isDestroy = false;
		for (list<Component*>::iterator itr = m_listComponent->begin(); itr != m_listComponent->end(); itr++)
			(*itr)->Init();
	}

	void Release()
	{
		for (list<Component*>::iterator itr = m_listComponent->begin(); itr != m_listComponent->end(); itr++)
		{
			(*itr)->Release();
			delete(*itr);
			(*itr) = nullptr;
		}
		delete m_listComponent;
		m_listComponent = nullptr;
	}

	void Start()
	{
		for (list<Component*>::iterator itr = m_listComponent->begin(); itr != m_listComponent->end(); itr++)
			(*itr)->Start();
	}

	void Update()
	{
		if (!m_setActive)
			return;

		for (list<Component*>::iterator itr = m_listComponent->begin(); itr != m_listComponent->end(); itr++)
			(*itr)->Update();
	}
};

