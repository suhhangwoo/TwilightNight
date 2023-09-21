#include "TextBtn.h"
#include"Buffer.h"
#include"WindowFrame.h"
#include"Mouse.h"


TextBtn::TextBtn(GameObject* gameObj,HWND hwnd):Component(gameObj),m_hWnd(hwnd)
{
}

void TextBtn::Init()
{
}

void TextBtn::Release()
{
}

void TextBtn::Start()
{

}

void TextBtn::Update()
{


}


bool TextBtn::WeaponHave()
{
	list<GameObject*>* gameObj = ObjectMGR::GetInstance()->GetObjList();
	for (list<GameObject*>::iterator itr = gameObj->begin(); itr != gameObj->end(); itr++)
	{
		if ((*itr)->GetTag() == weapon) {
			return true;
		}
	}

	return false;
}

void TextBtn::SetSelect()
{
	random_device rd;
	mt19937 rng(rd());

	uniform_int_distribution<int> dist(1, 5);
	m_select = dist(rng);
}

void TextBtn::SetEffect()
{
	random_device rd;
	mt19937 rng(rd());

	uniform_int_distribution<int> dist(1, 4);

	m_effect = (SelectNum)dist(rng);

	RECT rect;
	GetClientRect(m_hWnd, &rect);
	GameObject* tmp;
	
	TextChange(m_effect);

	KillTimer(m_hWnd, TIMER_UPDATE);
	tmp = UIMGR::GetInstance()->FindObject("Timer");
	((TimeCtrl*)tmp->GetComponent<TimeCtrl>())->StartStopWatch();



	list<GameObject*>* uiObj = UIMGR::GetInstance()->List();

	for (list<GameObject*>::iterator itr = uiObj->begin(); itr != uiObj->end(); itr++)
	{
		if ((*itr)->GetTag() == "Icon")
			((IconCtrl*)(*itr)->GetComponent<IconCtrl>())->Event();
		if ((*itr)->GetTag() == "Text")
			((TextCtrl*)(*itr)->GetComponent<TextCtrl>())->Event();
	}

}

void TextBtn::Event()
{
	((SndCtrl*)m_gameObj->GetComponent<SndCtrl>())->PlaySndEffect();
	SetTimer(m_hWnd, TIMER_UPDATE, TIMER_UPDATE_UNIT, NULL);
	list<GameObject*>* uiObj = UIMGR::GetInstance()->List();
	for (list<GameObject*>::iterator itr = uiObj->begin(); itr != uiObj->end(); itr++)
	{
		if ((*itr)->GetTag() == "Icon") {
			((IconCtrl*)(*itr)->GetComponent<IconCtrl>())->SetIcon(nullptr);
			(*itr)->SetActive(false);
		}
		if ((*itr)->GetTag() == "Text") {
			((TextCtrl*)(*itr)->GetComponent<TextCtrl>())->SetText(nullptr);
			(*itr)->SetActive(false);
		}
		if ((*itr)->GetTag() == "Test")
			(*itr)->SetActive(false);

	}
	Effect(m_effect);
	GameObject* tmp = UIMGR::GetInstance()->FindObject("Timer");
	((TimeCtrl*)tmp->GetComponent<TimeCtrl>())->StartStopWatch();;
}

void TextBtn::Kind()
{

	switch (m_select)
	{
	case WeaponKind::ROUND:
		weapon = "Weapon.Round";
		icon = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(IC_ROUND));
		break;
	case WeaponKind::SHOOT:
		weapon = "Weapon.Shoot";
		icon = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(IC_SHOOT));
		break;
	case WeaponKind::BOUNCE:
		weapon = "Weapon.Bounce";
		icon = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(IC_BOUNCE));
		break;
	case WeaponKind::FALL:
		weapon = "Weapon.Fall";
		icon = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(IC_FALL));
		break;
	case WeaponKind::LAST:
		weapon = "Weapon.Last";
		icon = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(IC_LAST));
		break;
	default:
		break;
	}


}

void TextBtn::TextChange(SelectNum select)
{
	switch (select) {
	case SelectNum::WEAPON_ADD:
		if (WeaponHave()) {
			txt = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(TXT_HPPLUS));
			icon = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(IDB_FRAME));
			break;
		}
		else {
			txt = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(TXT_WADD));
			break;
		}
	case SelectNum::BULLET_PLUS:
		if (WeaponHave()) {
			txt = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(TXT_WPLUS));
		}
		else {
			txt = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(TXT_HPPLUS));
			icon = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(IDB_FRAME));
		}
		break;
	case SelectNum::DAMAGE_UP:
		if (WeaponHave()) {
			txt = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(TXT_DMGPLUS));
		}
		else {
			txt = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(TXT_HPPLUS));
			icon = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(IDB_FRAME));
		}
		break;
	case SelectNum::SPEED_UP:
		if (WeaponHave()) {
			txt = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(TXT_SPDPLUS));
		}
		else {
			txt = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(TXT_HPPLUS));
			icon = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(IDB_FRAME));
		}
		break;
	}
}

void TextBtn::Effect(SelectNum select)
{
	int a=0, s=0;
	switch (select) {
	case SelectNum::WEAPON_ADD:
		if (WeaponHave()) {
			GameObject* tmp = UIMGR::GetInstance()->FindObject("HPBar");
			((HPBar*)tmp->GetComponent<HPBar>())->Event(-2000);
			break;
		}
		else {
			ObjectMGR::GetInstance()->AddObject((ObjectMGR::GetInstance()->CreateWeapon(m_select)));
			break;
		}
	case SelectNum::BULLET_PLUS:
		if (WeaponHave()) {
			ObjectMGR::GetInstance()->AddObject((ObjectMGR::GetInstance()->CreateWeapon(m_select)));
		}
		else {
			GameObject* tmp = UIMGR::GetInstance()->FindObject("HPBar");
			((HPBar*)tmp->GetComponent<HPBar>())->Event(-2000);
		}

		break;
	case SelectNum::DAMAGE_UP:
		if (WeaponHave()) {
			a = 1;
		}
		else {
			GameObject* tmp = UIMGR::GetInstance()->FindObject("HPBar");
			((HPBar*)tmp->GetComponent<HPBar>())->Event(-2000);
		}

		break;
	case SelectNum::SPEED_UP:
		if (WeaponHave()) {
			s = 1;
		}
		else {
			GameObject* tmp = UIMGR::GetInstance()->FindObject("HPBar");
			((HPBar*)tmp->GetComponent<HPBar>())->Event(-2000);
		}

		break;
	}
	WeaponSetting(a, s);
}

void TextBtn::WeaponSetting(int atk,int spd)
{
	list<GameObject*>* gameObj = ObjectMGR::GetInstance()->GetObjList();
	for (list<GameObject*>::iterator itr = gameObj->begin(); itr != gameObj->end(); itr++)
	{
		if ((*itr)->GetTag() == weapon) {
			((Bullet*)(*itr)->GetComponent<Bullet>())->SetAtk(atk);
			((Bullet*)(*itr)->GetComponent<Bullet>())->SetSpd(spd);
		}
	}
}


TCHAR* TextBtn::Text(SelectNum select)
{
	switch (select) {
	case SelectNum::WEAPON_ADD:
		if (WeaponHave()) {
			wsprintf(m_txt, TEXT("HP 20 회복"));
			break;
		}
		else {
			wsprintf(m_txt, TEXT("%d번 무기 추가"), m_select);
			break;
		}
	case SelectNum::BULLET_PLUS:
		wsprintf(m_txt, TEXT("%d번 무기 생성"), m_select);
		break;
	case SelectNum::DAMAGE_UP:
		wsprintf(m_txt, TEXT("%d번 무기 공격력 증가"), m_select);
		break;
	case SelectNum::SPEED_UP:
		wsprintf(m_txt, TEXT("%d번 무기 속도 증가"), m_select);
		break;
	}

	return m_txt;
}
