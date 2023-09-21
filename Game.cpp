#include "Game.h"
#include "CreateUI.h"
#include "UIMGR.h"
Game* Game::m_Pthis = nullptr;

HBITMAP Game::ResizeBitmap(HBITMAP hBitmap, int scaleX, int scaleY)
{
	BITMAP bitmapInfo;
	GetObject(hBitmap, sizeof(BITMAP), &bitmapInfo);
	int originalWidth = bitmapInfo.bmWidth;
	int originalHeight = bitmapInfo.bmHeight;

	int newWidth = originalWidth * scaleX;
	int newHeight = originalHeight * scaleY;

	m_buffer->MakeHDC();

	HDC hdcScreen = m_buffer->GetHDC();
	HDC hdcSrc = CreateCompatibleDC(hdcScreen);
	HDC hdcDest = CreateCompatibleDC(hdcScreen);

	HBITMAP hNewBitmap = CreateCompatibleBitmap(hdcScreen, newWidth, newHeight);
	HBITMAP hOldSrcBitmap = static_cast<HBITMAP>(SelectObject(hdcSrc, hBitmap));
	HBITMAP hOldDestBitmap = static_cast<HBITMAP>(SelectObject(hdcDest, hNewBitmap));

	StretchBlt(hdcDest, 0, 0, newWidth, newHeight, hdcSrc, 0, 0, originalWidth, originalHeight, SRCCOPY);

	SelectObject(hdcSrc, hOldSrcBitmap);
	SelectObject(hdcDest, hOldDestBitmap);
	DeleteDC(hdcSrc);
	DeleteDC(hdcDest);

	m_buffer->DeleteHDC();
	return hNewBitmap;
}

void Game::Create()
{
	if (!m_Pthis)
	{
		m_Pthis = new Game();

	}
}

Game* Game::GetInstance()
{
	return m_Pthis;
}

void Game::Destroy()
{
	if (m_Pthis)
	{
		delete m_Pthis;
		m_Pthis = nullptr;
	}
}

void Game::DrawBitmap(HDC hdc, int x, int y, int w, int h, HBITMAP hbit, UINT color)
{
	HDC MemoryDC;
	int BitmapX, BitmapY;
	BITMAP Bitmap_;
	HBITMAP OldBitmap;
	MemoryDC = CreateCompatibleDC(hdc);
	OldBitmap = (HBITMAP)SelectObject(MemoryDC, hbit);
	GetObject(hbit, sizeof(BITMAP), &Bitmap_);
	BitmapX = Bitmap_.bmWidth;
	BitmapY = Bitmap_.bmHeight;
	TransparentBlt(hdc, x, y, w, h, MemoryDC, 0, 0, BitmapX, BitmapY, color);
	SelectObject(MemoryDC, OldBitmap);
	DeleteDC(MemoryDC);
}

void Game::DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit)
{
	HDC MemDC;
	HBITMAP OldBitmap;
	int bx, by;
	BITMAP bit;

	MemDC = CreateCompatibleDC(hdc);
	OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);

	GetObject(hBit, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	BitBlt(hdc, x, y, bx, by, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}

void Game::Init(Buffer* buffer, HWND hWnd, int mapScaleX, int mapScaleY)
{
	srand(time(NULL));
	
	CMouse::GetInstance()->Initialize();
	m_buffer = buffer;
	m_hWnd = hWnd;

	m_bg = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(BITMAP_BG));
	m_frame = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(IDB_FRAME));
	m_title = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(TXT_TITLE));
	m_click = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(TXT_CLKSCN));
	m_player = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(IDB_FRAME));
	m_rClick = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(TXT_CLKR));
	m_lClick = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(TXT_CLKL));
	m_end = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(TXT_END));
	GetObject(m_bg, sizeof(BITMAP), &m_bgInfo);
	RECT cRect = { 0 };
	GetClientRect(m_hWnd, &cRect);
	m_buffer->Init(hWnd, mapScaleX, mapScaleY);
	float bgScaleX = (float)m_buffer->GetBitmapInfo().bmWidth / (float)m_bgInfo.bmWidth;
	float bgScaleY = (float)m_buffer->GetBitmapInfo().bmHeight / (float)m_bgInfo.bmHeight;
	m_bgResize = ResizeBitmap(m_bg, bgScaleX, bgScaleY);
	BITMAP bgResizeInfo = { 0 };
	GetObject(m_bgResize, sizeof(BITMAP), &bgResizeInfo);
	m_bgResizeInfo.X = bgResizeInfo.bmWidth;
	m_bgResizeInfo.Y = bgResizeInfo.bmHeight;

	ObjectMGR::Create();
	ObjectMGR::GetInstance()->CreateAnim();

	UIMGR::Create();

	CreateGame();
	UIMGR::GetInstance()->AllSetActive(false);
	ObjectMGR::GetInstance()->AllSetActive(false);

	ScreenTitle();
}

void Game::Release()
{
	ObjectMGR::GetInstance()->ReleaseAnim();
	ObjectMGR::GetInstance()->Release();
	UIMGR::GetInstance()->Release();
	ObjectMGR::Destroy();
	UIMGR::Destroy();
	DeleteObject(m_bgResize);
	DeleteObject(m_bg);
	KillTimer(m_hWnd, TIMER_UPDATE);
	m_buffer->Release();
}

void Game::StartGame() 
{
	UIMGR::GetInstance()->AddObject(Profile(m_hWnd, 0, 0, 100, 100, m_sex));
	UIMGR::GetInstance()->AllSetActive(true);
	ObjectMGR::GetInstance()->AllSetActive(true);
	SetTimer(m_hWnd, TIMER_UPDATE, TIMER_UPDATE_UNIT, NULL);
	((TimeCtrl*)timer->GetComponent<TimeCtrl>())->StartStopWatch();
}

void Game::Update()
{
	switch (m_state)
	{

	case E_GAMESTATE::GAME:
	{
		MobSumon();
		//임시 배경
		m_buffer->MakeHDC();

		this->DrawBitmap(m_buffer->GetHDC(), 0 - GetPlayerSize().X / 2, 0 - GetPlayerSize().Y / 2, m_bgResize);

		m_buffer->DeleteHDC();
		//
		ObjectMGR::GetInstance()->Update();
		UIMGR::GetInstance()->Update();
		//

		InvalidateRect(m_hWnd, NULL, FALSE);
		break;
	}
	}
}

void Game::MobSumon()
{
	m_time++;

	if (m_time % 100 == 0) 
	{
		ObjectMGR::GetInstance()->AddObject((ObjectMGR::GetInstance()->CreateZombie(150, 200)));
	}
	if (m_time % 1000 == 0) 
	{
		ObjectMGR::GetInstance()->MakeCoffinGroup();
	}
	if (m_time % 2000 == 0) {
		ObjectMGR::GetInstance()->MakeBatGroup();
	}
}

void Game::CreateGame()
{
	BITMAP info = m_buffer->GetBitmapInfo();
	ObjectMGR::GetInstance()->AddObject(ObjectMGR::GetInstance()->CreatePlayer(info.bmWidth / 2, info.bmHeight / 2, 150, 200,true));

	UIMGR::GetInstance()->AddObject(CreateBarBG(m_hWnd, 100, 30, 510, 30));
	UIMGR::GetInstance()->AddObject(CreateBarBG(m_hWnd, 100, 0, 510, 30));
	UIMGR::GetInstance()->AddObject(CreateHPBar(m_hWnd, 103, 5, 500, 15));
	UIMGR::GetInstance()->AddObject(CreateLevelBar(m_hWnd, 107, 37, 500, 15));
	UIMGR::GetInstance()->AddObject(CreateLevel(m_hWnd, 100, 52, 50, 50));
	UIMGR::GetInstance()->AddObject(CreateTestBtn(m_hWnd, 150, 100, 200, 300, 1));
	UIMGR::GetInstance()->AddObject(CreateTestBtn(m_hWnd, 450, 100, 200, 300, 2));
	UIMGR::GetInstance()->AddObject(CreateTestBtn(m_hWnd, 750, 100, 200, 300, 3));
	UIMGR::GetInstance()->AddObject(CreateIcon(m_hWnd, 150, 100, 200, 300, 1));
	UIMGR::GetInstance()->AddObject(CreateIcon(m_hWnd, 450, 100, 200, 300, 2));
	UIMGR::GetInstance()->AddObject(CreateIcon(m_hWnd, 750, 100, 200, 300, 3));
	UIMGR::GetInstance()->AddObject(CreateText(m_hWnd, 150, 100, 200, 300, 1));
	UIMGR::GetInstance()->AddObject(CreateText(m_hWnd, 450, 100, 200, 300, 2));
	UIMGR::GetInstance()->AddObject(CreateText(m_hWnd, 750, 100, 200, 300, 3));
	UIMGR::GetInstance()->AddObject(CreateTimer(m_hWnd,0,100));
	ObjectMGR::GetInstance()->AddObject(BGSnd());

	timer = UIMGR::GetInstance()->FindObject("Timer");
	((TimeCtrl*)timer->GetComponent<TimeCtrl>())->StartStopWatch();
	GameObject* tmp = ObjectMGR::GetInstance()->FindObject("bgm");
	((SndCtrl*)tmp->GetComponent<SndCtrl>())->PlaySndBgm();

}

void Game::SetInGame(bool b)
{
	m_IsInGame = b;
}

bool Game::GetInGame()
{
	return m_IsInGame;
}

COORD Game::GetPlayerPos()
{
	GameObject* player = ObjectMGR::GetInstance()->FindObject("Player");
	COORD pos;
	pos.X = player->Position()->X;
	pos.Y = player->Position()->Y;

	return pos;
}

COORD Game::GetPlayerSize()
{
	GameObject* player = ObjectMGR::GetInstance()->FindObject("Player");
	COORD pos;
	pos.X = player->Size()->X;
	pos.Y = player->Size()->Y;

	return pos;
}


void Game::LBtnDown()
{
	switch (m_state)
	{
	case E_GAMESTATE::TITLE:
		m_state = E_GAMESTATE::SELECT;
		ScreenSelect();
		break;
	case E_GAMESTATE::SELECT:
		m_state = E_GAMESTATE::GAME;
		StartGame();
		break;
	case E_GAMESTATE::END:
		m_state = E_GAMESTATE::TITLE;
		ScreenTitle();
		break;
	}
}

void Game::RBtnDown()
{
	
}

void Game::LBtnUp()
{
	list<GameObject*>* uiObj = UIMGR::GetInstance()->List();
	for (list<GameObject*>::iterator itr = uiObj->begin(); itr != uiObj->end(); itr++)
	{
		if ((*itr)->GetTag() == "Test"&&(*itr)->GetActive()){
			if (((BtnObject*)(*itr)->GetComponent<BtnObject>())->Check(m_hWnd)) {
				((TextBtn*)(*itr)->GetComponent<TextBtn>())->Event();
				break;
			}
		}	
	}
}

void Game::RBtnUp()
{
	GameObject* tmp = UIMGR::GetInstance()->FindObject("LevelBar");
	((Level*)tmp->GetComponent<Level>())->Event();
	//((TextRender*)tmp->GetComponent<TextRender>())->ChangeText(((Level*)tmp->GetComponent<Level>())->Text());
}

void Game::KeyDown(WPARAM wParam)
{
	switch (m_state)
	{
	case E_GAMESTATE::GAME:
	{
		switch (wParam)
		{
		case 'B':
			ObjectMGR::GetInstance()->MakeBatGroup();
			break;
		case 'C':
			ObjectMGR::GetInstance()->MakeCoffinGroup();
			break;
		case 'Z':
			ObjectMGR::GetInstance()->AddObject((ObjectMGR::GetInstance()->CreateZombie(150, 200)));
			break;
		}
		break;
	}
	case E_GAMESTATE::SELECT:
	{
		switch (wParam)
		{
		case VK_LEFT:
			//여캐릭 선택
		{
			m_sex = false;
			Update();
			GameObject* player = ObjectMGR::GetInstance()->FindObject("Player");
			((BitmapRender*)player->GetComponent<BitmapRender>())->ChangeBitmap(ObjectMGR::GetInstance()->GetPlayerAnim(false)->BitDataList()->begin()->origin);
			((AnimationRender*)player->GetComponent<AnimationRender>())->ChangeAnim(ObjectMGR::GetInstance()->GetPlayerAnim(false));

			ObjectMGR::GetInstance()->AddObject((ObjectMGR::GetInstance()->CreateWeapon(1)));
			ObjectMGR::GetInstance()->AddObject((ObjectMGR::GetInstance()->CreateWeapon(1)));
			ObjectMGR::GetInstance()->AddObject((ObjectMGR::GetInstance()->CreateWeapon(2)));
			ObjectMGR::GetInstance()->AddObject((ObjectMGR::GetInstance()->CreateWeapon(3)));

			Update();
			m_state = E_GAMESTATE::GAME;
			StartGame();
		}
		break;
		case VK_RIGHT:
			//남캐릭 선택
		{
			m_sex = true;
			Update();
			GameObject* player = ObjectMGR::GetInstance()->FindObject("Player");
			((BitmapRender*)player->GetComponent<BitmapRender>())->ChangeBitmap(ObjectMGR::GetInstance()->GetPlayerAnim(true)->BitDataList()->begin()->origin);
			((AnimationRender*)player->GetComponent<AnimationRender>())->ChangeAnim(ObjectMGR::GetInstance()->GetPlayerAnim(true));

			ObjectMGR::GetInstance()->AddObject((ObjectMGR::GetInstance()->CreateWeapon(4)));
			ObjectMGR::GetInstance()->AddObject((ObjectMGR::GetInstance()->CreateWeapon(4)));
			ObjectMGR::GetInstance()->AddObject((ObjectMGR::GetInstance()->CreateWeapon(5)));
			ObjectMGR::GetInstance()->AddObject((ObjectMGR::GetInstance()->CreateWeapon(5)));

			Update();
			m_state = E_GAMESTATE::GAME;
			StartGame();
		}
		break;
		}
		break;
	}
	}
}

COORD Game::GetBgResizeInfo()
{
	return m_bgResizeInfo;
}

void Game::GameEnd()
{

	ObjectMGR::GetInstance()->AllSetActive(false);
	UIMGR::GetInstance()->AllSetActive(false);
	ObjectMGR::GetInstance()->DeleteAllObject();
	UIMGR::GetInstance()->DeleteAllObject();
	m_state = E_GAMESTATE::END;
	KillTimer(m_hWnd, TIMER_UPDATE);
	CreateGame();

}

void Game::ScreenTitle()
{

	RECT rt;
	GetClientRect(m_hWnd, &rt);
	m_buffer->MakeHDC();
	DrawBitmap(m_buffer->GetHDC(), 0, 0, rt.right, rt.bottom, m_bg, RGB(0, 0, 0));

	DrawBitmap(m_buffer->GetHDC(), 300, 100, 500, 200, m_title, RGB(255,0,0));

	DrawBitmap(m_buffer->GetHDC(), 400, 400, 250, 80, m_click, RGB(255, 0, 0));
	m_buffer->DeleteHDC();
	
	InvalidateRect(m_hWnd, NULL, true);
}

void Game::ScreenSelect()
{
	RECT rt;
	GetClientRect(m_hWnd, &rt);
	m_buffer->MakeHDC();
	DrawBitmap(m_buffer->GetHDC(), 0, 0, rt.right, rt.bottom, m_bg, RGB(0, 0, 0));


	DrawBitmap(m_buffer->GetHDC(), (rt.right/2)-350, 100, 200, 400, m_frame, RGB(0, 0, 0));
	DrawBitmap(m_buffer->GetHDC(), (rt.right / 2) - 350, 100, 200, 400, 
		LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(BITMAP_PLAYER_0)), 
		RGB(0, 255, 87)); //여캐
	DrawBitmap(m_buffer->GetHDC(), (rt.right / 2) - 350, 50, 200, 100, m_lClick, RGB(255, 0, 0));


	DrawBitmap(m_buffer->GetHDC(), (rt.right / 2) + 150, 100, 200, 400,m_frame, RGB(0, 0, 0));
	DrawBitmap(m_buffer->GetHDC(), (rt.right / 2) + 150, 100, 200, 400,
		LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(P_MALE1)),
		RGB(0, 255, 87)); //남캐
	DrawBitmap(m_buffer->GetHDC(), (rt.right / 2) + 150, 50, 200, 100, m_rClick, RGB(255, 0, 0));

	m_buffer->DeleteHDC();

	InvalidateRect(m_hWnd, NULL, true);
}

void Game::ScreenEnd()
{
	RECT rt;
	GetClientRect(m_hWnd, &rt);
	m_buffer->MakeHDC();
	DrawBitmap(m_buffer->GetHDC(), 0, 0, rt.right, rt.bottom, m_bg, RGB(0, 0, 0));
	DrawBitmap(m_buffer->GetHDC(), 0, 0, rt.right, rt.bottom, m_end, RGB(255, 0, 0));
	m_buffer->DeleteHDC();

	InvalidateRect(m_hWnd, NULL, true);
}
