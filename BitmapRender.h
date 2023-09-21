#pragma once
#include "Global.h"
#include "Component.h"
#include "WindowFrame.h"
#include "Buffer.h"
#include "GameObject.h"

class WindowFrame;

class BitmapRender : public Component
{
private:
	HBITMAP m_bit = { 0 };
	UINT m_transColor;

	void DrawBitmap(HDC hdc, int x, int y, int w, int h, HBITMAP hbit, UINT color);
	
public:
	BitmapRender(GameObject* gameObj, HBITMAP hbit, UINT transColor); 

	void Init() override;
	void Release() override;
	void ChangeBitmap(HBITMAP hbit);
	void Start() override;
	void Update() override;
};

