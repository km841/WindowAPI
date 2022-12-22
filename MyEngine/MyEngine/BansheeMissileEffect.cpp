#include "pch.h"
#include "BansheeMissileEffect.h"
#include "BansheeBullet.h"
#include "EventRegisteror.h"
#include "Monster.h"
#include "Animator.h"
#include "Animation.h"

BansheeMissileEffect::BansheeMissileEffect()
	:mAttFlag(false)
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
	// 12방향으로 미사일을 쏘고 false 반환 
	// AttDelay를 더 주는 걸로
	float initAngle = 15.f;
	
	if (false == mAttFlag)
	{
		for (int i = 0; i < 12; ++i)
		{
			BansheeBullet* bullet = new BansheeBullet;
			bullet->SetPos(GetPos());

			Vec2 initDir = Math::RotateVector(Vec2(1, 0), Math::DegreeToRadian(initAngle + (i * 30.f)));
			bullet->SetDir(initDir);

			EventRegisteror::GetInstance().CreateObject(bullet, bullet->GetType());
		}

		mAttFlag = true;
	}


	Animation* anim = GetOwner()->GetAnimator()->GetCurAnimation();
	if (nullptr != anim)
	{
		if (anim->IsFinished())
		{
			mAttFlag = false;
			return false;
		}
		else
			return true;
	}

	return false;
}
