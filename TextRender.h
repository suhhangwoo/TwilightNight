#pragma once
#include "Component.h"
#include "GameObject.h"
class TextRender : public Component
{
private:
	HFONT m_font = { 0 };
	TCHAR* m_txt = TEXT("txt");
	COORD m_position = { 0,0 };
	COLORREF color;

	void DrawTxt(HDC hdc, int x, int y, TCHAR* txt, HFONT hfont);

public:
	TextRender(GameObject* gameObj, HFONT hfont, TCHAR* txt, COORD position,COLORREF c);

	void Init() override;
	void Release() override;
	void Start() override;
	void Update() override;
	

	void ChangeText(TCHAR* txt);

	void ChangeFont(HFONT cFont);

};

