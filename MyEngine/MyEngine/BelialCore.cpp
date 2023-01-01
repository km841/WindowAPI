#include "pch.h"
#include "BelialCore.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Animator.h"
#include "BelialCoreParticle.h"
#include "EventRegisteror.h"
#include "TimeMgr.h"
#include "CameraMgr.h"
#include "BelialCoreBullet.h"
#include "Animation.h"

BelialCore::BelialCore()
	: mMaxDuration(0.2f)
	, mCurDuration(0.f)
	, mMaxFired(24.f)
	, mCurFired(0.f)
	, mInitAngle(0.f)
	, mShotMaxDuration(0.1f)
	, mShotCurDuration(0.f)
{
	SetType(OBJECT_TYPE::DUMMY);
	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	Texture* tex = ResourceMgr::GetInstance().Load<Texture>(L"Belial_Back_Tex", L"Texture\\Monster\\Belial\\Belial_Back_Anim.bmp");

	GetAnimator()->RegisterAnimation(
		L"BelialBackAnim",
		tex,
		Vec2(0, 0),
		Vec2(150, 150),
		Vec2(150, 0),
		0.1f,
		10
	);

	GetAnimator()->SelectAnimation(L"BelialBackAnim", true);
}

BelialCore::~BelialCore()
{
}

void BelialCore::Update()
{
	//Particle Update
	Effect::Update();

	// 랜덤 방향

	if (mMaxDuration < mCurDuration)
	{
		mCurDuration = 0.f;
		Vec2 initVec = Vec2(1, 0);
		float randAngle = Math::DegreeToRadian((float)(rand() % 360));
		Vec2 randomDir = Math::RotateVector(initVec, randAngle);

		BelialCoreParticle* particle = new BelialCoreParticle;
		particle->SetDir(randomDir);

		Vec2 particlePos = GetPos();
		particlePos += Vec2(0, -30);

		particle->SetPos(particlePos);
		EventRegisteror::GetInstance().CreateObject(particle, particle->GetType());
	}

	else
	{
		mCurDuration += DT;
	}
}

void BelialCore::Render()
{
	//Particle Render
	GameObject::Render();

	Vec2 particlePos = GetPos();

}

bool BelialCore::Attack()
{
	// N초동안 각도를 회전시킨 공을 발사
	if (mMaxFired < mCurFired)
	{
		mInitAngle = 0.f;
		mCurFired = 0.f;
		mShotCurDuration = 0.f;
		return false;
	}

	else
	{
		if (mShotMaxDuration < mShotCurDuration)
		{
			mShotCurDuration = 0.f;
			for (int i = 0; i < NUM_SHOTS; ++i)
			{
				BelialCoreBullet* bullet = new BelialCoreBullet;
				Vec2 curPos =GetPos();
				curPos.y -= 50.f;

				bullet->SetPos(curPos);

				float angle = mInitAngle + (i * 90.f);
				float radian = Math::DegreeToRadian(angle);
				bullet->SetDir(Math::RotateVector(Vec2(1, 0), radian));
				
				EventRegisteror::GetInstance().CreateObject(bullet, bullet->GetType());
			}

			mInitAngle += 10.f;
			++mCurFired;
		}

		else
		{
			mShotCurDuration += DT;
		}
	}



	return true;
}

void BelialCore::Dead()
{
	GetAnimator()->SelectAnimation(L"BelialBackAnim", true);
	GetAnimator()->GetCurAnimation()->Reset();
	GetAnimator()->GetCurAnimation()->SetFrameFix(true);



}
