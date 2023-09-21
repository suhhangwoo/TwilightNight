#include"TextRender.h"
#include "WindowFrame.h"
#include "Buffer.h"

void TextRender::DrawTxt(HDC hdc, int x, int y, TCHAR* txt, HFONT hfont)
{
	HFONT OldFont;
	OldFont = (HFONT)SelectObject(hdc, hfont);
	SetTextColor(hdc, color);
	SetBkMode(hdc, TRANSPARENT); // 글자 배경 투명화
	TextOut(hdc, x, y, txt, lstrlen(txt));
	SelectObject(hdc, OldFont);
}

TextRender::TextRender(GameObject* gameObj, HFONT hfont, TCHAR* txt, COORD position, COLORREF c)
	: Component(gameObj), m_font(hfont), m_txt(txt), m_position(position),color(c) {}

void TextRender::Init()
{
}

void TextRender::Release()
{
}

void TextRender::Start()
{
}

void TextRender::Update()
{
	Buffer* buffer = CWindowFrame::GetInstance()->GetBuffer();
	buffer->MakeHDC();
	DrawTxt(buffer->GetHDC(),
		m_gameObj->Position()->X + m_position.X, m_gameObj->Position()->Y + m_position.Y, m_txt, m_font);
	buffer->DeleteHDC();
}

void TextRender::ChangeText(TCHAR* txt)
{
	m_txt = txt;
}

void TextRender::ChangeFont(HFONT cFont)
{
	m_font = cFont;
}
