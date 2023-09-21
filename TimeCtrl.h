#pragma once
#include"Component.h"
#include"UIMGR.h"
#include"ObjectMGR.h"
#include"TextRender.h"
#include<Windows.h>

class TimeCtrl :public Component {
private:
	DWORD startTime = 0;
	DWORD Time = 0;
	DWORD pauseTime = 0;
	TCHAR m_time[100];
	HWND m_hWnd;
	bool runGame = false;
public:
	TimeCtrl(GameObject* object,HWND hwnd):Component(object),m_hWnd(hwnd) {}

	void Timer() {
		if (runGame) {
			Time = GetTickCount64() - startTime+pauseTime;
		}
	}

	void RunStop(bool m);
	void StartStopWatch() {
		if (runGame) {
			Time = GetTickCount64() - startTime + pauseTime;
			pauseTime = Time;
			runGame = false;
		}
		else {
			startTime = GetTickCount64();
			runGame = true;
		}
	}

	int GetTime() { return Time; }
	void GetTimer(DWORD ms, TCHAR* time, int size);
	void Reset();
	void Init() override{}
	void Release() override{}
	void Start() override;
	void Update() override;

};