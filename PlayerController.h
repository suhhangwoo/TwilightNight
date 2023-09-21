#pragma once
#include "Component.h"
#include "GameObject.h"
#include "WindowFrame.h"

class AnimationRender;

struct DIR
{
	double x;
	double y;
};

class PlayerController : public Component
{
private :
	int m_speed;
	DIR m_dir = { 0 };
	AnimationRender* m_ar = nullptr;
private:
	void VectorNormalize(DIR* vector)
	{
		double d = sqrt((vector->x * vector->x) + (vector->y * vector->y));
		vector->x = vector->x / d;
		vector->y = vector->y / d;
	}
public:
	//�����ڿ��� �θ������ �̷��� �ݵ�� ȣ���ؾ� ��
	PlayerController(GameObject* gameObj, int spd);

	void SetSpeed(int spd);
	DIR GetDir();
	void Init() override;
	void Release() override;
	void Start() override;
	void Update() override;
};

