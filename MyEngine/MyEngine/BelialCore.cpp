#include "pch.h"
#include "BelialCore.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Animator.h"
#include "BelialCoreParticle.h"
#include "EventRegisteror.h"
#include "TimeMgr.h"
#include "CameraMgr.h"

BelialCore::BelialCore()
	:mMaxDuration(0.2f)
	,mCurDuration(0.f)
{
	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	Texture* tex = ResourceMgr::GetInstance().Load<Texture>(L"Belial_Back_Tex", L"Texture\\Belial_Back_Anim.bmp");

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

	// ·£´ý ¹æÇâ

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
	return false;
}
