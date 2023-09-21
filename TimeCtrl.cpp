#include "TimeCtrl.h"

void TimeCtrl::RunStop(bool m)
{
	runGame = m;
}

void TimeCtrl::GetTimer(DWORD ms, TCHAR* time, int size)
{
	DWORD seconds = ms / 1000;
	DWORD minutes = seconds / 60;
	seconds %= 60;

	wsprintf(time, TEXT("%02d : %02d"), minutes, seconds);
}

void TimeCtrl::Reset()
{
	Time = 0;
	startTime = 0;
	pauseTime = 0;
}

void TimeCtrl::Start()
{
	StartStopWatch();
}

void TimeCtrl::Update()
{
	Timer();
	if (runGame)
		GetTimer(Time, m_time, sizeof(m_time));
	else 
		GetTimer(pauseTime, m_time, sizeof(m_time));
	((TextRender*)m_gameObj->GetComponent<TextRender>())->ChangeText(m_time);
}
