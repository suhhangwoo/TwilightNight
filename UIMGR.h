#pragma once
#include "resource.h"
#include <string>
#include <list>
#include"Game.h"

using namespace std;

class GameObject;

class UIMGR
{
private:
	static UIMGR* m_Pthis;
	list<GameObject*>* m_objList = nullptr;
public:
	static void Create();
	static UIMGR* GetInstance();
	static void Destroy();


	void AllSetActive(bool active);
	void DeleteAllObject();
	list<GameObject*>* List();
	void AddObject(GameObject* obj);
	bool UIMGR::DeleteObject(GameObject* obj);
	bool DeleteObject(string tag);
	GameObject* FindObject(string tag);
	void Release();
	void Update();
};

