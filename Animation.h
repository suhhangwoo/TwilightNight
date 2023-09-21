#pragma once
#include "list"
#include <Windows.h>

using namespace std;

struct BITDATA
{
	HBITMAP origin;
	HBITMAP origin_flipx;
};
class Animation
{
private:
	list<int>* m_bitIDList = nullptr;
	list<BITDATA>* m_bitDataList = nullptr;
	int m_UpdateTime = 10;

	HBITMAP CreateBitmapFlipX(HDC hdc, HBITMAP hbit);
	void Init();
	void Release();
public:
	Animation(list<int>* bitIDList, int updateTime);
	~Animation();
	
	list<int>* BitIDList();
	list<BITDATA>* BitDataList();
	int GetUpdateTime();
	void SetUpdate(int updateTime);
};

