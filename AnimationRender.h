#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Animation.h"

class BitmapRender;

class AnimationRender : public Component
{
private:
	BitmapRender* m_bitRender = nullptr;
	Animation* m_anim = nullptr;
	int m_updateTimer = 0;
	list<BITDATA>::iterator m_itr;
	bool m_isPlay = false;
	bool m_isFlipX = false;
	bool m_isFx = false;
public:
	AnimationRender(GameObject* gameObj, Animation* anim, bool isFx) : Component(gameObj), m_anim(anim), m_isFx(isFx) {}

	void Init() override;
	void Release() override;
	void Start() override;
	void Update() override;
	Animation* GetAnim() { return m_anim; }
	void ChangeAnim(Animation* anim)
	{
		m_anim = anim;
		m_updateTimer = 0;
		m_itr = m_anim->BitDataList()->begin();
	}

	void SetPlay(bool isPlay);

	void SetFlipX(bool isFlip);
};

