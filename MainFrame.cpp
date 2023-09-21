#include "MainFrame.h"

CMainFrame* CMainFrame::mPthis = nullptr;

void CMainFrame::Create(HINSTANCE hInstance)
{
	if (!mPthis)
	{
		mPthis = new CMainFrame();
		CWindowFrame::Create(hInstance);
		CMouse::Create();
	}
}

CMainFrame* CMainFrame::GetInstance()
{
	return mPthis;
}

void CMainFrame::Destroy()
{
	if (mPthis)
	{
		CMouse::Destroy();
		CWindowFrame::Destroy();
		delete mPthis;
		mPthis = nullptr;
	}
}

void CMainFrame::Initialize()
{
	CWindowFrame::GetInstance()->BuildWindow();
}

int CMainFrame::Run()
{
	MSG Message;
	while (GetMessage(&Message, NULL, 0, 0)) 
	{
		CWindowFrame::GetInstance()->Run(&Message);
	}
	return (int)Message.wParam;
}
