#include "pch.h"
#include "BelialCoreParticle.h"
#include "Animator.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Animation.h"
#include "TimeMgr.h"

BelialCoreParticle::BelialCoreParticle()
	: mSpeed(120.f)
{
	SetType(OBJECT_TYPE::PARTICLE);
	mTex = ResourceMgr::GetInstance().Load<Texture>(L"BelialCore_ParticleTex", L"Texture\\Belial_Back_Particle_Anim.bmp");

	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	GetAnimator()->RegisterAnimation(
		L"BelialCore_ParticleAnim",
		mTex,
		Vec2(0, 0),
		Vec2(90, 90),
		Vec2(90, 0),
		0.1f,
		9
	);


	GetAnimator()->SelectAnimation(L"BelialCore_ParticleAnim", false);
}

BelialCoreParticle::~BelialCoreParticle()
{
}

void BelialCoreParticle::Initialize()
{
	GameObject::Initialize();
}

void BelialCoreParticle::Update()
{
	GameObject::Update();

	Animation* anim = GetAnimator()->GetCurAnimation();
	if (nullptr != anim)
	{
		if (anim->IsFinished())
		{
			SetObjState(OBJECT_STATE::DEAD);
		}

		else
		{
			Vec2 pos = GetPos();
			pos += mDir * mSpeed * DT;
			SetPos(pos);
		}
	}

}

void BelialCoreParticle::Render()
{
	GameObject::Render();
}

void BelialCoreParticle::Destroy()
{
	GameObject::Destroy();
}
