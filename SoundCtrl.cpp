#include "SoundCtrl.h"

void SndCtrl::Init()
{
	mciOpen.lpstrElementName = m_Snd; // 파일 경로 입력
	mciOpen.lpstrDeviceType = "mpegvideo";
}

void SndCtrl::Start()
{
	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE,
		(DWORD)(LPVOID)&mciOpen);

	dwID = mciOpen.wDeviceID;
}
