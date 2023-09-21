#include "WeaponController_Bounce.h"

#include <cmath>
#include <random>

#include "ObjectMGR.h"

static int ResetStack = 0;

 void WeaponController_Bounce::getRandomAngle() {
	 const double PI = 3.14159265358979323846;

	 std::random_device rd;
	 std::mt19937 gen(rd());
	 std::uniform_real_distribution<float> dis(0.0f, 360.0f);

	 float degree = dis(gen);
	 m_radians = (degree * PI) / 180.0f;
}

 void WeaponController_Bounce::Update()
 {
	 int atk = ((Bullet*)m_gameObj->GetComponent<Bullet>())->GetAtk();
	 int spd = ((Bullet*)m_gameObj->GetComponent<Bullet>())->GetSpd();
	 GameObject* tmp = ObjectMGR::GetInstance()->FindObject("Player");
	 RECT rt;
	 GetClientRect(CWindowFrame::GetInstance()->GetHWND(), &rt);

	 float dx = spd * 4 * cos(m_radians);
	 float dy = spd * 4 * sin(m_radians);

	 m_gameObj->Position()->X += dx;
	 m_gameObj->Position()->Y -= dy;

	 if (m_gameObj->Position()->X < (tmp->Position()->X - (rt .right/2) + m_gameObj->Size()->X)
		 || m_gameObj->Position()->X >(tmp->Position()->X + (rt.right / 2) + m_gameObj->Size()->X)) {
		 m_radians = 180.0f - m_radians; // x축 충돌하면
		 dx = (spd *4) * cos(m_radians);
		 dy = (spd *4) * sin(m_radians);
		 m_gameObj->Position()->X += dx;
		 m_gameObj->Position()->Y -= dy;

		 ResetStack++;
	 }
	 if (m_gameObj->Position()->Y < (tmp->Position()->Y - (rt.bottom / 2) + (m_gameObj->Size()->Y*2))
		 || m_gameObj->Position()->Y > (tmp->Position()->Y +(rt.bottom / 2) + m_gameObj->Size()->Y)) {
		 m_radians = -m_radians; // y축 충돌하면
		 dx = (spd * 4) * cos(m_radians);
		 dy = (spd * 4) * sin(m_radians);
		 m_gameObj->Position()->X += dx;
		 m_gameObj->Position()->Y -= dy;

		 ResetStack++;
	 }

	 //For Bug...
	 if (ResetStack > 50) {
		 Reset();
	 }
 }

 void WeaponController_Bounce::Reset() {
	 ResetStack = 0;

	 GameObject* tmp = ObjectMGR::GetInstance()->FindObject("Player");

	 int xRand = rand() % 60;
	 int yRand = rand() % 90;
	 m_gameObj->Position()->X = tmp->Position()->X + xRand;
	 m_gameObj->Position()->Y = tmp->Position()->Y + 30 + yRand;

	 getRandomAngle();

 }