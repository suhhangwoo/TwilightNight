#include "ObjectMGR.h"
#include "GameObject.h"
#include "Global.h"

ObjectMGR* ObjectMGR::m_Pthis = nullptr;
const double PI = 3.14159265358979323846;
void ObjectMGR::Create()
{
	if (!m_Pthis)
	{
		m_Pthis = new ObjectMGR();
		m_Pthis->m_objList = new list<GameObject*>();
		m_Pthis->m_objList = new list<GameObject*>();

		m_Pthis->m_tmp = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(IDB_BITMAP5));
		m_Pthis->m_Round = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(IDB_ROUND));
		m_Pthis->m_coffinBit = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(IDB_BITMAP17));
	}
}

ObjectMGR* ObjectMGR::GetInstance()
{
	return m_Pthis;
}

void ObjectMGR::Destroy()
{
	if (m_Pthis)
	{
		::DeleteObject(m_Pthis->m_tmp);

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

void ObjectMGR::AddObject(GameObject* obj)
{
	m_objList->push_back(obj);
	obj->Init();
	obj->Start();
}


bool ObjectMGR::DeleteObject(GameObject* obj)
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

bool ObjectMGR::DeleteObject(string tag)
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

void ObjectMGR::DeleteAllObject()
{
	for (list<GameObject*>::iterator itr = m_Pthis->m_objList->begin(); itr != m_Pthis->m_objList->end(); itr++)
	{
		(*itr)->SetDestroy(true);
	}
}

void ObjectMGR::AllSetActive(bool active)
{
	for (list<GameObject*>::iterator itr = m_Pthis->m_objList->begin(); itr != m_Pthis->m_objList->end(); itr++)
	{
		(*itr)->SetActive(active);
	}
}

GameObject* ObjectMGR::FindObject(string tag)
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

void ObjectMGR::Release()
{
	for (list<GameObject*>::iterator itr = m_objList->begin(); itr != m_objList->end(); itr++)
	{
		(*itr)->Release();
	}
}

void ObjectMGR::Update() //버그나면 여기일 확률이 크다 (해결완료)
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

void ObjectMGR::CreateAnim()
{
	list<int>* animList_player = new list<int>();
	animList_player->push_back(BITMAP_PLAYER_1);
	animList_player->push_back(BITMAP_PLAYER_4);
	animList_player->push_back(BITMAP_PLAYER_5);
	animList_player->push_back(BITMAP_PLAYER_6);
	m_playerAnim = new Animation(animList_player, 20);

	list<int>* animList_player_male = new list<int>();
	animList_player_male->push_back(P_MALE1);
	animList_player_male->push_back(P_MALE2);
	animList_player_male->push_back(P_MALE3);
	animList_player_male->push_back(P_MALE4);
	m_playerAnim_male = new Animation(animList_player_male, 20);

	list<int>* animList_zombie = new list<int>();
	animList_zombie->push_back(IDB_BITMAP12);
	animList_zombie->push_back(IDB_BITMAP13);
	animList_zombie->push_back(IDB_BITMAP14);
	m_zombieAnim = new Animation(animList_zombie, 20);

	list<int>* animList_bat = new list<int>();
	animList_bat->push_back(IDB_BITMAP15);
	animList_bat->push_back(IDB_BITMAP16);
	m_batAnim = new Animation(animList_bat, 20);

	list<int>* animList_Fall = new list<int>();
	animList_Fall->push_back(IDB_BITMAP19);
	animList_Fall->push_back(IDB_BITMAP20);
	animList_Fall->push_back(IDB_BITMAP22);
	animList_Fall->push_back(IDB_BITMAP23);
	m_fallAnim = new Animation(animList_Fall, 8);

	list<int>* animList_Shoot = new list<int>();
	animList_Shoot->push_back(IDB_BITMAP24);
	animList_Shoot->push_back(IDB_BITMAP25);
	m_shootAnim = new Animation(animList_Shoot, 5);

	list<int>* animList_Bounce = new list<int>();
	animList_Bounce->push_back(IDB_BOUNCE1);
	animList_Bounce->push_back(IDB_BOUNCE2);
	m_bounceAnim = new Animation(animList_Bounce, 5);

	list<int>* animList_Round = new list<int>();
	animList_Round->push_back(IDB_ROUND1);
	animList_Round->push_back(IDB_ROUND2);
	animList_Round->push_back(IDB_ROUND3);
	animList_Round->push_back(IDB_ROUND4);
	m_roundAnim = new Animation(animList_Round, 5);

	list<int>* FxList = new list<int>();
	//
	FxList->clear();
	m_Fx[0] = new Animation(FxList, 2);

	FxList->clear();
	for (int i = IDB_BITMAP87; i <= IDB_BITMAP92; i++)
		FxList->push_back(i);
	m_Fx[1] = new Animation(FxList, 2);

	FxList->clear();
	for (int i = IDB_BITMAP79; i <= IDB_BITMAP86; i++)
		FxList->push_back(i);
	m_Fx[2] = new Animation(FxList, 2);

	FxList->clear();
	for (int i = IDB_BITMAP71; i <= IDB_BITMAP78; i++)
		FxList->push_back(i);
	m_Fx[3] = new Animation(FxList, 2);

	FxList->clear();
	for (int i = FX_fall1; i <= FX_fall7; i++)
		FxList->push_back(i);
	m_Fx[4] = new Animation(FxList, 2);

	FxList->clear();
	for (int i = IDB_LAST1; i <= IDB_LAST31; i++)
		FxList->push_back(i);
	m_Fx[5] = new Animation(FxList, 2);
	/*list<int>* animList_Last = new list<int>();
	for (int i = IDB_LAST1; i <= IDB_LAST31; i++) {
		animList_Last->push_back(i);
	}
	m_lastAnim = new Animation(animList_Last, 20);*/
}

void ObjectMGR::ReleaseAnim()
{
	delete m_playerAnim;
	delete m_zombieAnim;
	delete m_batAnim;
	delete m_fallAnim;
	delete m_shootAnim;
	delete m_roundAnim;
	delete m_bounceAnim;
	delete m_playerAnim_male;

	m_batAnim = nullptr;
	m_zombieAnim = nullptr;
	m_playerAnim = nullptr;
	m_playerAnim_male = nullptr;
	m_roundAnim = nullptr;
	m_fallAnim = nullptr;
	m_shootAnim = nullptr;
	m_bounceAnim = nullptr;

	for (int i = 0; i < 6; i++)
	{
		delete m_Fx[i];
		m_Fx[i] = nullptr;
	}
}

GameObject* ObjectMGR::CreatePlayer(int x, int y, int sizeX, int sizeY, bool isMale)
{
	GameObject* player = new GameObject();
	player->SetTag("Player");
	player->Position()->X = x;
	player->Position()->Y = y;
	player->Size()->X = sizeX;
	player->Size()->Y = sizeY;

	player->AddComponent(new PlayerController(player, 5));
	player->AddComponent(new PlayerController(player, 5));
	if (isMale)
	{
		player->AddComponent(new BitmapRender(player, m_playerAnim_male->BitDataList()->begin()->origin, RGB(0, 255, 87)));
		player->AddComponent(new AnimationRender(player, m_playerAnim_male, false));
	}
	else
	{
		player->AddComponent(new BitmapRender(player, m_playerAnim->BitDataList()->begin()->origin, RGB(0, 255, 87)));
		player->AddComponent(new AnimationRender(player, m_playerAnim, false));
	}
	return player;
}

list<GameObject*>* ObjectMGR::GetObjList()
{
	return m_objList;
}

GameObject* ObjectMGR::CreateWeapon(int kind)
{
	GameObject* tmp = ObjectMGR::GetInstance()->FindObject("Player");

	GameObject* weapon = new GameObject();

	weapon->Position()->X = tmp->Position()->X;
	weapon->Position()->Y = tmp->Position()->Y;
	AnimationRender* shootAr;
	//추후 비트맵 및 크기 수정필요
	switch (kind) 
	{
	case 1:
		weapon->Size()->X = 50;
		weapon->Size()->Y = 50;
		weapon->SetTag("Weapon.Round");
		weapon->AddComponent(new BitmapRender(weapon, m_roundAnim->BitDataList()->begin()->origin, RGB(0, 0, 0)));
		weapon->AddComponent(new WeaponController_Round(weapon));
		weapon->AddComponent(new Bullet(weapon));
		weapon->AddComponent(shootAr = new AnimationRender(weapon, m_roundAnim, false));
		shootAr->SetPlay(true);
		break;
	case 2:
		weapon->Size()->X = 50;
		weapon->Size()->Y = 50;
		weapon->SetTag("Weapon.Shoot");
		weapon->AddComponent(new BitmapRender(weapon, m_shootAnim->BitDataList()->begin()->origin, RGB(255, 255, 255)));
		weapon->AddComponent(new WeaponController_Shoot(weapon));
		weapon->AddComponent(new Bullet(weapon));
		weapon->AddComponent(shootAr = new AnimationRender(weapon, m_shootAnim, false));
		shootAr->SetPlay(true);
		break;
	case 3:
		weapon->Size()->X = 50;
		weapon->Size()->Y = 50;
		weapon->SetTag("Weapon.Bounce");
		weapon->AddComponent(new BitmapRender(weapon, m_bounceAnim->BitDataList()->begin()->origin, RGB(255, 255, 255)));
		weapon->AddComponent(new WeaponController_Bounce(weapon));
		weapon->AddComponent(new Bullet(weapon));
		weapon->AddComponent(shootAr = new AnimationRender(weapon, m_bounceAnim, false));
		shootAr->SetPlay(true);


		break;
	case 4:
		weapon->Size()->X = 80;
		weapon->Size()->Y = 80;
		weapon->SetTag("Weapon.Fall");
		weapon->AddComponent(new BitmapRender(weapon, m_fallAnim->BitDataList()->begin()->origin, RGB(255, 255, 255)));
		weapon->AddComponent(new WeaponController_Fall(weapon));
		weapon->AddComponent(new Bullet(weapon));
		AnimationRender* fallAr;
		weapon->AddComponent(fallAr = new AnimationRender(weapon, m_fallAnim, false));
		fallAr->SetPlay(true);

		break;
	case 5:
		weapon->Size()->X = 150;
		weapon->Size()->Y = 150;
		weapon->SetTag("Weapon.Last");
		
		weapon->AddComponent(new WeaponController_Last(weapon));
		weapon->AddComponent(new Bullet(weapon));
	
		break;
	default:
		break;
	}

	weapon->AddComponent(new SndCtrl(weapon, TEXT("mopdie.wav")));
	//((AnimationRender*)weapon->GetComponent<AnimationRender>())->SetPlay(true);
	return weapon;
}

GameObject* ObjectMGR::CreateZombie(int sizeX, int sizeY)
{
	RECT crt;
	GameObject* player = ObjectMGR::GetInstance()->FindObject("Player");

	GetClientRect(CWindowFrame::GetInstance()->GetHWND(), &crt);

	int dir = rand() % 4;

	GameObject* zombie = new GameObject();
	zombie->SetTag("Enemy");
	zombie->Size()->X = sizeX;
	zombie->Size()->Y = sizeY;

	switch (dir)
	{
	case 0: //위
		zombie->Position()->X = (rand() % (player->Position()->X + (crt.right / 2) + 100)) - 50;
		zombie->Position()->Y = player->Position()->Y - (crt.bottom / 2) - 50;
		break;
	case 1: //아래
		zombie->Position()->X = (rand() % (player->Position()->X + (crt.right / 2) + 100)) - 50;
		zombie->Position()->Y = player->Position()->Y + (crt.bottom / 2) + 50;
		break;
	case 2: //왼쪽
		zombie->Position()->X = player->Position()->X - (crt.right / 2) - 50;
		zombie->Position()->Y = (rand() % (player->Position()->Y + (crt.bottom / 2) + 100)) - 50;
		break;
	case 3: //오른쪽
		zombie->Position()->X = player->Position()->X + (crt.right / 2) + 50;
		zombie->Position()->Y = (rand() % (player->Position()->Y + (crt.bottom / 2) + 100)) - 50;
		break;
	}

	zombie->AddComponent(new Zombie(zombie));
	zombie->AddComponent(new BitmapRender(zombie, m_zombieAnim->BitDataList()->begin()->origin, RGB(0, 255, 87)));
	AnimationRender* zombieAr;
	zombie->AddComponent(zombieAr = new AnimationRender(zombie, m_zombieAnim, false));
	zombieAr->SetPlay(true);
	return zombie;
}

GameObject* ObjectMGR::CreateCoffin(int x, int y, int sizeX, int sizeY)
{
	GameObject* coffin = new GameObject();
	coffin->SetTag("Enemy");
	coffin->Position()->X = x;
	coffin->Position()->Y = y;
	coffin->Size()->X = sizeX;
	coffin->Size()->Y = sizeY;

	coffin->AddComponent(new Coffin(coffin));
	coffin->AddComponent(new BitmapRender(coffin, m_coffinBit, RGB(0, 255, 87)));
	return coffin;
}

GameObject* ObjectMGR::CreateBat(int x, int y, int vx, int vy, int sizeX, int sizeY)
{
	GameObject* player = ObjectMGR::GetInstance()->FindObject("Player");
	GameObject* bat = new GameObject();
	bat->SetTag("Enemy");
	bat->Position()->X = x;
	bat->Position()->Y = y;
	bat->Size()->X = sizeX;
	bat->Size()->Y = sizeY;

	bat->AddComponent(new Bat(bat, vx, vy));
	bat->AddComponent(new BitmapRender(bat, m_batAnim->BitDataList()->begin()->origin, RGB(0, 255, 87)));
	AnimationRender* batAr;
	bat->AddComponent(batAr = new AnimationRender(bat, m_batAnim, false));
	batAr->SetPlay(true);

	if (player->Position()->X > bat->Position()->X)
	{
		((AnimationRender*)bat->GetComponent<AnimationRender>())->SetFlipX(true);
	}
	else
	{
		((AnimationRender*)bat->GetComponent<AnimationRender>())->SetFlipX(false);
	}

	return bat;
}

void ObjectMGR::RandomXY(SHORT* x, SHORT* y)
{
	RECT crt;
	GameObject* player = ObjectMGR::GetInstance()->FindObject("Player");
	GetClientRect(CWindowFrame::GetInstance()->GetHWND(), &crt);
	int dir = rand() % 4;

	switch (dir)
	{
	case 0: //위
		*x = (rand() % (player->Position()->X + (crt.right / 2) + 100)) - 50;
		*y = player->Position()->Y - (crt.bottom / 2) - 50;
		break;
	case 1: //아래
		*x = (rand() % (player->Position()->X + (crt.right / 2) + 100)) - 50;
		*y = player->Position()->Y + (crt.bottom / 2) + 50;
		break;
	case 2: //왼쪽
		*x = player->Position()->X - (crt.right / 2) - 50;
		*y = (rand() % (player->Position()->Y + (crt.bottom / 2) + 100)) - 50;
		break;
	case 3: //오른쪽
		*x = player->Position()->X + (crt.right / 2) + 50;
		*y = (rand() % (player->Position()->Y + (crt.bottom / 2) + 100)) - 50;
		break;
	}
}

void ObjectMGR::MakeCoffinGroup()
{
	GameObject* player = ObjectMGR::GetInstance()->FindObject("Player");

	float x, y;
	float r = 300;

	for (int theta = 0; theta <= 400; theta += 40)
	{
		x = player->Position()->X + r * cos(theta);
		y = player->Position()->Y + r * sin(theta);
		ObjectMGR::GetInstance()->AddObject((ObjectMGR::GetInstance()->CreateCoffin(x, y, 150, 200)));
	}
}

void ObjectMGR::MakeBatGroup()
{
	GameObject* player = ObjectMGR::GetInstance()->FindObject("Player");
	SHORT mx, my;
	SHORT px = player->Position()->X;
	SHORT py = player->Position()->Y;
	int r = 200;

	RandomXY(&mx, &my);

	float d = sqrt((px - mx) * (px - mx) + (py - my) * (py - my));
	float vx = (px - mx) / d * 15;
	float vy = (py - my) / d * 15;

	for (int i = 0; i < 20; i++)
	{
		float theta = 2.0 * PI * (static_cast<float>(rand()) / RAND_MAX);
		float distance = r * sqrt(static_cast<float>(rand()) / RAND_MAX);

		float x = mx + distance * cos(theta);
		float y = my + distance * sin(theta);

		ObjectMGR::GetInstance()->AddObject((ObjectMGR::GetInstance()->CreateBat(x, y, vx, vy, 150, 200)));
	}
}

bool ObjectMGR::CheckScreenOut(int x, int y)
{
	RECT crt;
	GameObject* player = ObjectMGR::GetInstance()->FindObject("Player");

	GetClientRect(CWindowFrame::GetInstance()->GetHWND(), &crt);

	if (x > (player->Position()->X + (crt.right / 2) + 50) || x < (player->Position()->X - (crt.right / 2) - 50))
	{
		if (y > (player->Position()->Y + (crt.bottom / 2) + 50) || y < (player->Position()->Y - (crt.bottom / 2) - 50))
		{
			return true;
		}
	}
	return false;
}

Animation* ObjectMGR::GetFx(int WeaponNum)
{
	return m_Fx[WeaponNum];
}

Animation* ObjectMGR::GetPlayerAnim(bool isMale)
{
	if (isMale)
		return m_playerAnim_male;

	return m_playerAnim;
}