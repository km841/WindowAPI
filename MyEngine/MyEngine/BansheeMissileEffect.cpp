#include "pch.h"
#include "BansheeMissileEffect.h"
#include "BansheeBullet.h"
#include "EventRegisteror.h"

BansheeMissileEffect::BansheeMissileEffect()
{
}

BansheeMissileEffect::~BansheeMissileEffect()
{
}

void BansheeMissileEffect::Initialize()
{
	MonsterMissileEffect::Initialize();
}

void BansheeMissileEffect::Update()
{
	MonsterMissileEffect::Update();
}

void BansheeMissileEffect::Render()
{
}

bool BansheeMissileEffect::Attack()
{
	// 12�������� �̻����� ��� false ��ȯ 
	// AttDelay�� �� �ִ� �ɷ�
	float initAngle = 15.f;
	
	for (int i = 0; i < 12; ++i)
	{
		BansheeBullet* bullet = new BansheeBullet;
		bullet->SetPos(GetPos());

		Vec2 initDir = Math::RotateVector(Vec2(1, 0), Math::DegreeToRadian(initAngle + (i * 30.f)));
		bullet->SetDir(initDir);

		EventRegisteror::GetInstance().CreateObject(bullet, bullet->GetType());
	}

	return false;
}
