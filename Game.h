#pragma once
#include "Global.h"
#include "GameObject.h"
#include "Component.h"
#include "ObjectMGR.h"
#include "Buffer.h"
enum class E_GAMESTATE
{
	TITLE,
	SELECT,
	GAME,
	END
};

class Game
{
private:
	static Game* m_Pthis;
private:
	GameObject* timer = nullptr;
	Buffer* m_buffer = nullptr;
	E_GAMESTATE m_state = E_GAMESTATE::TITLE;
	HWND m_hWnd = { 0 };
	bool m_IsInGame = true;
	HBITMAP m_bg = { 0 };
	HBITMAP m_frame = { 0 };
	HBITMAP m_title = { 0 };
	HBITMAP m_click = { 0 };
	HBITMAP m_player = { 0 };
	HBITMAP m_rClick = { 0 };
	HBITMAP m_lClick = { 0 };
	HBITMAP m_end = { 0 };

	int m_time = 0;

	bool m_sex = false;

	HBITMAP m_bgResize = { 0 };
	BITMAP m_bgInfo = { 0 };
	COORD m_bgResizeInfo = { 0, 0 };
	HBITMAP ResizeBitmap(HBITMAP hBitmap, int scaleX, int scaleY);
public:
	static void Create();
	static Game* GetInstance();
	static void Destroy();

	void DrawBitmap(HDC hdc, int x, int y, int w, int h, HBITMAP hbit, UINT color);
	void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit);
public:
	void Init(Buffer* buffer, HWND hWnd, int mapScaleX, int mapScaleY);
	void Release();
	void StartGame();
	void Update();

	void MobSumon();

	void CreateGame();

	//마우스 클릭 이벤트
	void LBtnDown();
	void RBtnDown();
	void LBtnUp();
	void RBtnUp();

	void KeyDown(WPARAM wParam);

	void SetInGame(bool b);
	bool GetInGame();
	COORD GetPlayerPos();
	COORD GetPlayerSize();
	COORD GetBgResizeInfo();

	void GameEnd();
	E_GAMESTATE GetState()
	{
		return m_state;
	}

	void ScreenTitle();
	void ScreenSelect();
	void ScreenEnd();

};

