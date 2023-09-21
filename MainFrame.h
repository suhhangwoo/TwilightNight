#pragma once
#include <windows.h>
#include "WindowFrame.h"
#include "Mouse.h"
class CMainFrame
{
private:
	static CMainFrame* mPthis;

	CMainFrame() {}
	~CMainFrame() {}
public:
	static void Create(HINSTANCE hInstance);
	static CMainFrame* GetInstance();
	static void Destroy();

	void Initialize();
	int Run();
};