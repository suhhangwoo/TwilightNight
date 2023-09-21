#include "Animation.h"
#include "Buffer.h"
#include "WindowFrame.h"
HBITMAP Animation::CreateBitmapFlipX(HDC hdc, HBITMAP hbit)
{
	HDC MemoryDC;
	int BitmapX, BitmapY;
	BITMAP Bitmap_;
	HBITMAP OldBitmap;
	MemoryDC = CreateCompatibleDC(hdc);
	OldBitmap = (HBITMAP)SelectObject(MemoryDC, hbit);
	GetObject(hbit, sizeof(BITMAP), &Bitmap_);
	BitmapX = Bitmap_.bmWidth;
	BitmapY = Bitmap_.bmHeight;

	// 비트맵을 뒤집어서 복사
	HBITMAP flippedBitmap = CreateCompatibleBitmap(hdc, BitmapX, BitmapY);
	HDC flippedDC = CreateCompatibleDC(hdc);
	HBITMAP oldFlippedBitmap = (HBITMAP)SelectObject(flippedDC, flippedBitmap);

	for (int y = 0; y < BitmapY; y++)
	{
		for (int x = 0; x < BitmapX; x++)
		{
			COLORREF color = GetPixel(MemoryDC, BitmapX - 1 - x, y);
			SetPixel(flippedDC, x, y, color);
		}
	}

	// 메모리 해제
	SelectObject(flippedDC, oldFlippedBitmap);
	DeleteDC(flippedDC);

	SelectObject(MemoryDC, OldBitmap);
	DeleteDC(MemoryDC);

	return flippedBitmap;
}

void Animation::Init()
{
	Buffer* buffer = CWindowFrame::GetInstance()->GetBuffer();
	m_bitDataList = new list<BITDATA>();
	for (list<int>::iterator itr = m_bitIDList->begin(); itr != m_bitIDList->end(); itr++)
	{
		buffer->MakeHDC();
		BITDATA data = { 0 };
		data.origin = LoadBitmap(CWindowFrame::GetInstance()->GetHInst(), MAKEINTRESOURCE(*itr));
		data.origin_flipx = CreateBitmapFlipX(buffer->GetHDC(), data.origin);
		m_bitDataList->push_back(data);
		buffer->DeleteHDC();
	}
}

void Animation::Release()
{
	for (list<BITDATA>::iterator itr = m_bitDataList->begin(); itr != m_bitDataList->end(); itr++)
	{
		DeleteObject(itr->origin);
		DeleteObject(itr->origin_flipx);
	}
	delete m_bitDataList;
}

Animation::Animation(list<int>* bitIDList, int updateTime) :m_bitIDList(bitIDList), m_UpdateTime(updateTime)
{
	Init();
}

Animation::~Animation()
{
	Release();
	if (m_bitIDList)
		delete m_bitIDList;
}

list<int>* Animation::BitIDList()
{
	return m_bitIDList; 
}

list<BITDATA>* Animation::BitDataList()
{
	return m_bitDataList;
}

int Animation::GetUpdateTime()
{
	return m_UpdateTime;
}

void Animation::SetUpdate(int updateTime)
{
	m_UpdateTime = updateTime;
}
