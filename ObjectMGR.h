#pragma once
#include "resource.h"
#include <string>
#include <list>
#include "PlayerController.h"
#include "BitmapRender.h"
#include "Animation.h"
#include "AnimationRender.h"
#include <Windows.h>

#include "WeaponController_Round.h"
#include "WeaponController_Shoot.h"
#include "WeaponController_Fall.h"
#include "WeaponController_Bounce.h"
#include "WeaponController_Last.h"

#include"Bullet.h"

#include "Zombie.h"
#include "Coffin.h"
#include"Bat.h"
#include<math.h>
#include"SoundCtrl.h"
//#include "AnimationMgr.h"

using namespace std;

class GameObject;

class ObjectMGR
{
private:
	static ObjectMGR* m_Pthis;
	list<GameObject*>* m_objList = nullptr;

	Animation* m_playerAnim = nullptr;
	Animation* m_playerAnim_male = nullptr;

	Animation* m_zombieAnim = nullptr;
	Animation* m_batAnim = nullptr;
	Animation* m_fallAnim = nullptr;
	Animation* m_shootAnim = nullptr;
	Animation* m_roundAnim = nullptr;
	Animation* m_lastAnim = nullptr;
	Animation* m_bounceAnim = nullptr;

	Animation* m_Fx[6] = { 0 };

	HBITMAP m_tmp = { 0 };
	HBITMAP m_Round = { 0 };
	HBITMAP m_coffinBit;
public:
	static void Create();
	static ObjectMGR* GetInstance();
	static void Destroy();

	void AddObject(GameObject* obj);
	bool ObjectMGR::DeleteObject(GameObject* obj);
	bool DeleteObject(string tag);
	void DeleteAllObject();
	void AllSetActive(bool active);
	GameObject* FindObject(string tag);
	void Release();
	void Update();
	list<GameObject*>* GetObjList();

	void CreateAnim();
	void ReleaseAnim();
	GameObject* CreatePlayer(int x, int y, int sizeX, int sizeY, bool isMale);

	GameObject* CreateWeapon(int kind);

	GameObject* CreateZombie(int sizeX, int sizeY);
	GameObject* CreateCoffin(int x, int y, int sizeX, int sizeY);
	GameObject* CreateBat(int x, int y, int vx, int vy, int sizeX, int sizeY);

	void RandomXY(SHORT* x, SHORT* y);
	void MakeCoffinGroup();
	void MakeBatGroup();
	bool CheckScreenOut(int x, int y);

	Animation* GetFx(int WeaponNum);
	Animation* GetPlayerAnim(bool isMale);
};

