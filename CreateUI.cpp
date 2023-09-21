#include"CreateUI.h"

HBITMAP m_hBit = nullptr;

GameObject* Profile(HWND m_hWnd,int x, int y, int sizeX, int sizeY,bool sex) {
	GameObject* profile = new GameObject();
	profile->SetTag("Profile");
	profile->Position()->X = x;
	profile->Position()->Y = y;
	profile->Size()->X = sizeX;
	profile->Size()->Y = sizeY;

	m_hBit = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(IDB_FACE));

	profile->AddComponent(new BitmapRender(profile, m_hBit, RGB(2, 255, 255)));

	if (sex) {
		m_hBit = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(IDB_MFACE));
	}
	else {
		m_hBit = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(IDB_GFACE));
	}

	profile->AddComponent(new BitmapRender(profile, m_hBit, RGB(0, 255, 87)));
	profile->AddComponent(new Position(profile,m_hWnd));


	return profile;
}

GameObject* CreateHPBar(HWND m_hWnd,int x, int y, int sizeX, int sizeY) {
	GameObject* HpBar = new GameObject();
	HpBar->SetTag("HPBar");
	HpBar->Position()->X = x;
	HpBar->Position()->Y = y;
	HpBar->Size()->X = sizeX;
	HpBar->Size()->Y = sizeY;

	m_hBit = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(IDB_HPBAR));

	HpBar->AddComponent(new Position(HpBar, m_hWnd));
	HpBar->AddComponent(new SndCtrl(HpBar, TEXT("hpdown.wav")));
	HpBar->AddComponent(new BitmapRender(HpBar, m_hBit, RGB(0, 0, 0)));
	HpBar->AddComponent(new HPBar(HpBar));


	return HpBar;
}

GameObject* CreateBarBG(HWND m_hWnd,int x, int y, int sizeX, int sizeY)
{
	GameObject* barBG = new GameObject();
	barBG->SetTag("BarBG");
	barBG->Position()->X = x;
	barBG->Position()->Y = y;
	barBG->Size()->X = sizeX;
	barBG->Size()->Y = sizeY;

	m_hBit = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(IDB_BARBG));

	barBG->AddComponent(new BitmapRender(barBG, m_hBit, RGB(255, 255, 255)));
	barBG->AddComponent(new Position(barBG, m_hWnd));


	return barBG;
}

GameObject* CreateLevelBar(HWND m_hWnd, int x, int y, int sizeX, int sizeY) {
	GameObject* level = new GameObject();
	level->SetTag("LevelBar");
	level->Position()->X = x;
	level->Position()->Y = y;
	level->Size()->X = sizeX;
	level->Size()->Y = sizeY;

	HFONT font = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("°íµñ"));
	COORD position = { x ,y };

	m_hBit = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(IDB_LEVELBAR));

	level->AddComponent(new SndCtrl(level, TEXT("levelup.wav")));
	level->AddComponent(new Level(level, m_hWnd));
	level->AddComponent(new BitmapRender(level, m_hBit, RGB(0, 0, 0)));
	level->AddComponent(new Position(level, m_hWnd));

	return level;
}

GameObject* CreateLevel(HWND m_hWnd,int x, int y, int sizeX, int sizeY)
{
	GameObject* level = new GameObject();
	level->SetTag("Level");
	level->Position()->X = x;
	level->Position()->Y = y;
	level->Size()->X = sizeX;
	level->Size()->Y = sizeY;

	HFONT font = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("°ß°íµñ"));
	COORD position = { (sizeX/2)-8 ,8 };
	m_hBit = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(IDB_LEVEL));

	level->AddComponent(new LevelCtrl(level));
	level->AddComponent(new BitmapRender(level, m_hBit, RGB(255, 255, 255)));
	level->AddComponent(new TextRender(level, font, TEXT("1"), position,RGB(255,0,0)));
	level->AddComponent(new Position(level, m_hWnd));

	return level;
}

GameObject* CreateTestBtn(HWND m_hWnd,int x, int y, int sizeX, int sizeY,int id)
{
	GameObject* test = new GameObject();
	test->SetTag("Test");
	test->Position()->X = x;
	test->Position()->Y = y;
	test->Size()->X = sizeX;
	test->Size()->Y = sizeY;
	test->SetActive(false);

	m_hBit = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(IDB_FRAME));

	test->AddComponent(new Position(test, m_hWnd));
	test->AddComponent(new SndCtrl(test, TEXT("levelup.wav")));
	test->AddComponent(new TextBtn(test,m_hWnd));
	test->AddComponent(new BitmapRender(test, m_hBit, RGB(0, 0, 0)));
	test->AddComponent(new BtnObject(test, id));

	return test;
}

GameObject* CreateTimer(HWND hwnd, int x, int y)
{
	GameObject* timer = new GameObject();
	timer->SetTag("Timer");
	timer->Position()->X = x;
	timer->Position()->Y = y;

	HFONT font = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("¸¼Àº°íµñ"));
	COORD position = { 0 ,0 };

	timer->AddComponent(new TextRender(timer, font, TEXT("00:00"), position,RGB(255,255,255)));
	timer->AddComponent(new TimeCtrl(timer, hwnd));
	timer->AddComponent(new Position(timer, hwnd));

	return timer;
}

GameObject* CreateIcon(HWND hwnd, int x, int y, int sizeX, int sizeY, int id)
{
	GameObject* test = new GameObject();
	test->SetTag("Icon");
	test->Position()->X = x;
	test->Position()->Y = y;
	test->Size()->X = sizeX;
	test->Size()->Y = sizeY;
	test->SetActive(false);

	test->AddComponent(new Position(test, hwnd));
	test->AddComponent(new IconCtrl(test, hwnd));
	test->AddComponent(new BtnObject(test, id));

	return test;
}

GameObject* CreateText(HWND hwnd, int x, int y, int sizeX, int sizeY, int id)
{
	GameObject* test = new GameObject();
	test->SetTag("Text");
	test->Position()->X = x;
	test->Position()->Y = y;
	test->Size()->X = sizeX;
	test->Size()->Y = sizeY;
	test->SetActive(false);

	test->AddComponent(new Position(test, hwnd));
	test->AddComponent(new TextCtrl(test, hwnd));
	test->AddComponent(new BtnObject(test, id));

	return test;
}

GameObject* BGSnd() {
	GameObject* bgm = new GameObject();
	bgm->SetTag("bgm");

	bgm->AddComponent(new SndCtrl(bgm,TEXT("bgm.wav")));

	return bgm;
}