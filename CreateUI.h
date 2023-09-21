#pragma once
#include"UIMGR.h"
#include"HPBarController.h"
#include"BitmapRender.h"
#include"LevelController.h"
#include"TextRender.h"
#include"TextBtn.h"
#include"BtnObject.h"
#include"SoundCtrl.h"
#include"TimeCtrl.h"
#include"ProfileCtrl.h"
#include"LevelCtrl.h"
#include"IconCtrl.h"
#include"TextCtrl.h"



GameObject* Profile(HWND m_hDnd, int x,int y,int sizeX,int sizeY,bool sex);
GameObject* CreateHPBar(HWND m_hWnd,int x, int y, int sizeX, int sizeY);
GameObject* CreateBarBG(HWND m_hWnd,int x, int y, int sizeX, int sizeY);
GameObject* CreateLevelBar(HWND m_hWnd, int x, int y, int sizeX, int sizeY);
GameObject* CreateLevel(HWND m_hWnd, int x, int y, int sizeX, int sizeY);
GameObject* CreateTestBtn(HWND m_hWNd,int x,int y,int sizeX,int sizeY,int id);
GameObject* CreateTimer(HWND hwnd, int x, int y);
GameObject* CreateIcon(HWND hwnd, int x, int y, int sizeX, int sizeY, int id);
GameObject* CreateText(HWND hwnd, int x, int y, int sizeX, int sizeY, int id);
GameObject* BGSnd();