#include "pch.h"
#include "Belial.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "BelialCore.h"


Belial::Belial()
{
	mMonType = MONSTER_TYPE::BOSS_BELIAL;
	SetGravity(false);
	Texture* mTex = ResourceMgr::GetInstance().Load<Texture>(L"Belial_Body_Tex", L"Texture\\Belial_Body_Anim.bmp");


	std::wstring idleAnimName = L"Belial_Idle";
	SetIdleAnimName(idleAnimName);

	GetCollider()->SetSize(Vec2(100, 100));
	GetCollider()->SetOffset(Vec2(25, -50));

	GetAnimator()->RegisterAnimation(
		idleAnimName,
		mTex,
		Vec2(0, 0),
		Vec2(210, 297),
		Vec2(210, 0),
		0.1f,
		10
	);

	GetAnimator()->RegisterAnimation(
		L"Belial_Attack_Open",
		mTex,
		Vec2(0, 297),
		Vec2(210, 384),
		Vec2(210, 0),
		0.1f,
		10
	);

	GetAnimator()->RegisterAnimation(
		L"Belial_Attack_Close",
		mTex,
		Vec2(0, 681),
		Vec2(210, 384),
		Vec2(210, 0),
		0.1f,
		10
	);

	GetAnimator()->FindAnimation(idleAnimName)->SetTransMode(true, 3.f, TRANS_MODE::FADE_IN);

	GetAnimator()->SelectAnimation(idleAnimName, true);
	
	BelialCore* belialCore = new BelialCore;
	belialCore->SetOwner(this);
	belialCore->SetOffset(Vec2(25, 0));

	SetEffect(belialCore);
	// 후방 Core는 Effect
	// Hand는? 이펙트인데 소멸자에서 따로 처리
}

Belial::~Belial()
{
}

void Belial::Initialize()
{
	//BossHPHUD 활성화
	//BelialCore 소환
	//Hand 2개 소환

	BossMonster::Initialize();

}

void Belial::Update()
{
	BossMonster::Update();
}

void Belial::Render()
{
	BossMonster::Render();
}

void Belial::Destroy()
{
	BossMonster::Destroy();
}

void Belial::OnCollision(Collider* _other)
{
}

void Belial::OnCollisionEnter(Collider* _other)
{
	BossMonster::OnCollisionEnter(_other);
}

void Belial::OnCollisionExit(Collider* _other)
{
}

bool Belial::Skill()
{
	return false;
}
