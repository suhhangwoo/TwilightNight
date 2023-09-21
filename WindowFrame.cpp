#include "WindowFrame.h"
#include "GameObject.h"
#include "Component.h"
#include "PlayerController.h"
#include "ObjectMGR.h"
#include"CreateUI.h"
CWindowFrame* CWindowFrame::m_Pthis = nullptr;

void CWindowFrame::Create(HINSTANCE hInstance)
{
	if (!m_Pthis)
	{
		m_Pthis = new CWindowFrame();
		m_Pthis->m_Instance = hInstance;
		m_Pthis->m_buffer = new Buffer();
	}
}

CWindowFrame* CWindowFrame::GetInstance()
{
	return m_Pthis;
}

void CWindowFrame::Destroy()
{
	if (m_Pthis)
	{
		delete m_Pthis->m_buffer;
		delete m_Pthis;
		m_Pthis = nullptr;
	}
}

LRESULT CWindowFrame::WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static HDC hdc;
	static PAINTSTRUCT ps;
	static GameObject* tmp;
	static COORD pos;
	static COORD size;
	switch (iMessage)
	{
	case WM_CREATE:
		m_Pthis->m_hWnd = hWnd;

		Game::Create();
		Game::GetInstance()->Init(m_Pthis->m_buffer, hWnd, 5, 5);

		pos = Game::GetInstance()->GetPlayerPos();
		size = Game::GetInstance()->GetPlayerSize();
		return 0;

	case WM_LBUTTONDOWN:
		CMouse::GetInstance()->SetLeftBtn(true);
		CMouse::GetInstance()->SetPos(LOWORD(lParam), HIWORD(lParam));
		Game::GetInstance()->LBtnDown();

		return 0;
	case WM_LBUTTONUP:
		CMouse::GetInstance()->SetLeftBtn(false);
		CMouse::GetInstance()->SetPos(LOWORD(lParam), HIWORD(lParam));
		Game::GetInstance()->LBtnUp();
		return 0;
	case WM_RBUTTONDOWN:
		CMouse::GetInstance()->SetRightBtn(true);
		CMouse::GetInstance()->SetPos(LOWORD(lParam), HIWORD(lParam));
		Game::GetInstance()->RBtnDown();
		return 0;
	case WM_RBUTTONUP:
		CMouse::GetInstance()->SetRightBtn(false);
		CMouse::GetInstance()->SetPos(LOWORD(lParam), HIWORD(lParam));
		Game::GetInstance()->RBtnUp();

		return 0;
	case WM_MOUSEMOVE:
		CMouse::GetInstance()->SetPos(LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_KEYDOWN:
		Game::GetInstance()->KeyDown(wParam);
		return 0;
	case WM_COMMAND:
		return 0;
	case WM_TIMER:
		if (wParam == TIMER_UPDATE)
		{
			Game::GetInstance()->Update();
		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		pos = Game::GetInstance()->GetPlayerPos();
		if (Game::GetInstance()->GetState() == E_GAMESTATE::GAME)
			m_Pthis->m_buffer->CopyBitmapGame(hdc, pos.X + size.X / 2, pos.Y + size.Y / 2);
		else
			m_Pthis->m_buffer->CopyBitmap(hdc);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		Game::GetInstance()->Release();
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void CWindowFrame::Initialize()
{

}

void CWindowFrame::BuildWindow()
{
	WNDCLASS WndClass;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = this->m_Instance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = TEXT("ÃÖ¿øÁØ");
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	this->m_hWnd = 
		CreateWindow(WndClass.lpszClassName, WndClass.lpszClassName, 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, this->m_Instance, NULL);

	ShowWindow(this->m_hWnd, SW_SHOW);
}

void CWindowFrame::Run(const MSG* Message)
{
	TranslateMessage(Message);
	DispatchMessage(Message);
}
