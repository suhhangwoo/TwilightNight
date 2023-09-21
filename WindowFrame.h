#pragma once
#include <windows.h>
#include "Mouse.h"
#include "Buffer.h"
#include "Global.h"
#include <stdlib.h>
#include <time.h>
#include "Game.h"

class CWindowFrame
{
private:
	static CWindowFrame* m_Pthis;

	HWND m_hWnd = NULL;
	HINSTANCE m_Instance = NULL;
	Buffer* m_buffer = nullptr;

	CWindowFrame() {}
	~CWindowFrame() {}
public:
	static void Create(HINSTANCE hInstance);
	static CWindowFrame* GetInstance();
	static void Destroy();

	//콜백함수는 static이어야 한다.
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	void Initialize();
	void BuildWindow();
	void Run(const MSG* Message);
	Buffer* GetBuffer() { return this->m_buffer; }
	HINSTANCE GetHInst() { return this->m_Instance; }
	HWND GetHWND() { return this->m_hWnd; }
};