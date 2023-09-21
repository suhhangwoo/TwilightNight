#include "BitmapRender.h"
#include "WindowFrame.h"
void BitmapRender::DrawBitmap(HDC hdc, int x, int y, int w, int h, HBITMAP hbit, UINT color)
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
	TransparentBlt(hdc, x, y, w, h, MemoryDC, 0, 0, BitmapX, BitmapY, color);
	SelectObject(MemoryDC, OldBitmap);
	DeleteDC(MemoryDC);
}

BitmapRender::BitmapRender(GameObject* gameObj, HBITMAP hbit, UINT transColor) : Component(gameObj), m_bit(hbit), m_transColor(transColor)
{
}

void BitmapRender::Init()
{
}

void BitmapRender::Release()
{
}

void BitmapRender::ChangeBitmap(HBITMAP hbit)
{
	m_bit = hbit;
}

void BitmapRender::Start()
{
}

void BitmapRender::Update()
{
	Buffer* buffer = CWindowFrame::GetInstance()->GetBuffer();
	buffer->MakeHDC();
	DrawBitmap(buffer->GetHDC(),
		m_gameObj->Position()->X, m_gameObj->Position()->Y,
		m_gameObj->Size()->X, m_gameObj->Size()->Y,
		m_bit, m_transColor);
	buffer->DeleteHDC();
}
