#include "Bullet.h"
#include "ObjectMGR.h"
#include "Enemy.h"
#include"UIMGR.h"
#include"CreateUI.h"
#include "AnimationRender.h"
void Bullet::Update() 
{
	GameObject* curDamaged = nullptr;
	list<GameObject*> *listTmp = ObjectMGR::GetInstance()->GetObjList();
	bool isColl = false;
	for (list<GameObject*>::iterator itr = listTmp->begin(); itr != listTmp->end(); itr++)
	{
		if ((*itr)->GetTag() == "Enemy") 
		{

			static RECT temp, enemyRt, myRt;
			myRt =
			{ m_gameObj->Position()->X - m_gameObj->Size()->X / 2,
			m_gameObj->Position()->Y - m_gameObj->Size()->Y / 2 ,
			m_gameObj->Position()->X + m_gameObj->Size()->X / 2 ,
			m_gameObj->Position()->Y + m_gameObj->Size()->Y / 2 };

			enemyRt =
			{ (*itr)->Position()->X - (*itr)->Size()->X / 2,
			(*itr)->Position()->Y - (*itr)->Size()->Y / 2 ,
			(*itr)->Position()->X + (*itr)->Size()->X / 2 ,
			(*itr)->Position()->Y + (*itr)->Size()->Y / 2 };
		
			
			if (IntersectRect(&temp, &myRt, &enemyRt)) //충돌 시
			{
				curDamaged = (*itr);
				if (curDamaged != m_BeforeDamaged ||
					curDamaged == nullptr)
				{
					//이펙트 발생
					GameObject* FX = new GameObject();
					FX->Position()->X = temp.left + (temp.right - temp.left) / 2;
					FX->Position()->Y = temp.top + (temp.bottom - temp.top) / 2;;
					FX->Size()->X = 100;
					FX->Size()->Y = 100;
					AnimationRender* ar = nullptr;
					if (m_gameObj->GetTag() == "Weapon.Round")
					{
						ar = new AnimationRender(FX, ObjectMGR::GetInstance()->GetFx(1), true);
						FX->AddComponent(new BitmapRender(FX, ar->GetAnim()->BitDataList()->begin()->origin, RGB(0, 0, 0)));
						FX->AddComponent(ar);
					}
					else if (m_gameObj->GetTag() == "Weapon.Shoot")
					{
						ar = new AnimationRender(FX, ObjectMGR::GetInstance()->GetFx(2), true);
						FX->AddComponent(new BitmapRender(FX, ar->GetAnim()->BitDataList()->begin()->origin, RGB(0, 0, 0)));
						FX->AddComponent(ar);
					}
					else if (m_gameObj->GetTag() == "Weapon.Bounce")
					{
						ar = new AnimationRender(FX, ObjectMGR::GetInstance()->GetFx(3), true);
						FX->AddComponent(new BitmapRender(FX, ar->GetAnim()->BitDataList()->begin()->origin, RGB(0, 0, 0)));
						FX->AddComponent(ar);
					}
					else if (m_gameObj->GetTag() == "Weapon.Fall")
					{
						ar = new AnimationRender(FX, ObjectMGR::GetInstance()->GetFx(4), true);
						FX->AddComponent(new BitmapRender(FX, ar->GetAnim()->BitDataList()->begin()->origin, RGB(0, 0, 0)));
						FX->AddComponent(ar);
					}
					else if (m_gameObj->GetTag() == "Weapon.Last")
					{
						FX->Size()->X = 200;
						FX->Size()->Y = 200;
						ar = new AnimationRender(FX, ObjectMGR::GetInstance()->GetFx(5), true);
						FX->AddComponent(new BitmapRender(FX, ar->GetAnim()->BitDataList()->begin()->origin, RGB(255, 255, 255)));
						FX->AddComponent(ar);
					}

					ar->SetPlay(true);
					ObjectMGR::GetInstance()->AddObject(FX);
					//
					Enemy* enemyTmp = static_cast<Enemy*>((*itr)->GetComponent<Zombie>());
					if (!enemyTmp)
						enemyTmp = static_cast<Enemy*>((*itr)->GetComponent<Coffin>());
					if(!enemyTmp)
						enemyTmp = static_cast<Enemy*>((*itr)->GetComponent<Bat>());

					if (!enemyTmp)//error
						return;

					(enemyTmp->SetHp(
						(enemyTmp->GetHp() - atk
							)));

				
					

					if (enemyTmp->GetHp() <= 0)
					{
						((SndCtrl*)m_gameObj->GetComponent<SndCtrl>())->PlaySndEffect();
						(*itr)->SetDestroy(true);
						GameObject* tmp = UIMGR::GetInstance()->FindObject("LevelBar");
						((Level*)tmp->GetComponent<Level>())->Event();
						
						tmp = UIMGR::GetInstance()->FindObject("Level");
						((TextRender*)tmp->GetComponent<TextRender>())->ChangeText(((LevelCtrl*)tmp->GetComponent<LevelCtrl>())->Text());
					}
					m_BeforeDamaged = curDamaged;
					return;
				}	
				m_BeforeDamaged = curDamaged;
				isColl = true;
			}
		}
	}
	if(!isColl)
	m_BeforeDamaged = nullptr;

}
