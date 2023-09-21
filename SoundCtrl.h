#pragma once
#include<Windows.h>
#pragma comment(lib, "winmm.lib")
#include <mmsystem.h>
#include "Digitalv.h"
#include"Component.h"
#include"UIMGR.h"

class SndCtrl : public Component {
private:
	TCHAR* m_Snd;
	MCI_OPEN_PARMS m_mciOpenParms;
	MCI_PLAY_PARMS m_mciPlayParms;
	DWORD m_dwDeviceID;
	MCI_OPEN_PARMS mciOpen;
	MCI_PLAY_PARMS mciPlay;
	int dwID;
public:
	SndCtrl(GameObject* object,TCHAR* file):Component(object),m_Snd(file){}

	void PlaySndEffect() {
		PlaySound(m_Snd, NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
	}

	void PlaySndBgm() {
		mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, // play & repeat
			(DWORD)(LPVOID)&m_mciPlayParms);
	}

	void Init() override;
	void Release() override{}
	void Start() override;
	void Update() override{}
};