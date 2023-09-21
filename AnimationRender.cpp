#include "AnimationRender.h"
#include "BitmapRender.h"
void AnimationRender::Init()
{
	m_bitRender = (BitmapRender*)Component::m_gameObj->GetComponent<BitmapRender>();
	m_itr = m_anim->BitDataList()->begin();
	m_bitRender->ChangeBitmap(m_itr->origin);
}

void AnimationRender::Release()
{
	m_bitRender = nullptr;
}

void AnimationRender::Start()
{
}

void AnimationRender::Update()
{
	if (!m_isPlay)
		return;

	m_updateTimer++;
	if (m_updateTimer < m_anim->GetUpdateTime())
		return;

	m_updateTimer = 0;
	m_itr++;
	if (m_itr == m_anim->BitDataList()->end())
	{
		if (m_isFx)
		{
			m_gameObj->SetDestroy(true);
			return;
		}
		else
			m_itr = m_anim->BitDataList()->begin();
	}

	if (m_isFlipX)
		m_bitRender->ChangeBitmap(m_itr->origin_flipx);
	else
		m_bitRender->ChangeBitmap(m_itr->origin);
}

void AnimationRender::SetPlay(bool isPlay)
{
	m_isPlay = isPlay;
	if (!m_isPlay)
	{
		m_itr = m_anim->BitDataList()->begin();
		if (m_isFlipX)
			m_bitRender->ChangeBitmap(m_itr->origin_flipx);
		else
			m_bitRender->ChangeBitmap(m_itr->origin);
	}
}

void AnimationRender::SetFlipX(bool isFlip)
{
	m_isFlipX = isFlip;
}
