#include "pch.h"
#include "GiantSkullWarrior.h"
#include "Collider.h"
#include "Animator.h"
#include "RigidBody.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Animation.h"

GiantSkullWarrior::GiantSkullWarrior()
{
	SetSize(Vec2(99.f, 90.f));

	GetCollider()->SetSize(Vec2(30.f, 30.f));
	GetCollider()->SetOffset(Vec2(0.f, -15.f));

	GetRigidBody()->SetMass(1.f);

	std::wstring idleAnimName = L"GiantSkull_Idle";
	SetIdleAnimName(idleAnimName);

	std::wstring moveAnimName = L"GiantSkull_Move";
	SetMoveAnimName(moveAnimName);
	
	std::wstring attAnimName = L"GiantSkull_Att";
	SetAttAnimName(attAnimName);
	
	Texture* animTex = ResourceMgr::GetInstance().Load<Texture>(L"GiantSkullAnimTex", L"Texture\\giant_skull_animation.bmp");

	GetAnimator()->RegisterAnimation(
		idleAnimName + L"Left",
		animTex,
		Vec2(0.f, 0.f),
		Vec2(99.f, 90.f),
		Vec2(99.f, 0.f),
		0.1f,
		6
	);

	GetAnimator()->RegisterAnimation(
		idleAnimName + L"Right",
		animTex,
		Vec2(0.f, 90.f),
		Vec2(99.f, 90.f),
		Vec2(99.f, 0.f),
		0.1f,
		6
	);

	GetAnimator()->RegisterAnimation(
		moveAnimName + L"Left",
		animTex,
		Vec2(0.f, 180.f),
		Vec2(99.f, 90.f),
		Vec2(99.f, 0.f),
		0.1f,
		6
	);

	GetAnimator()->RegisterAnimation(
		moveAnimName + L"Right",
		animTex,
		Vec2(0.f, 270.f),
		Vec2(99.f, 90.f),
		Vec2(99.f, 0.f),
		0.1f,
		6
	);

	Animation* attAnimLeft = GetAnimator()->CreateAnimation(
		attAnimName + L"Left",
		animTex,
		Vec2(0.f, 360.f),
		Vec2(213.f, 144.f),
		Vec2(213.f, 0.f),
		0.1f,
		12
	);

	attAnimLeft->SetOffset(Vec2(-50, 0));

	Animation* attAnimRight = GetAnimator()->CreateAnimation(
		attAnimName + L"Right",
		animTex,
		Vec2(0.f, 504.f),
		Vec2(213.f, 144.f),
		Vec2(213.f, 0.f),
		0.1f,
		12
	);

	attAnimRight->SetOffset(Vec2(50, 0));

	GetAnimator()->AddAnimation(attAnimName + L"Left", attAnimLeft);
	GetAnimator()->AddAnimation(attAnimName + L"Right", attAnimRight);


	GetAnimator()->SelectAnimation(L"GiantSkull_IdleLeft", true);
}

GiantSkullWarrior::~GiantSkullWarrior()
{
}

void GiantSkullWarrior::Initialize()
{
}

void GiantSkullWarrior::Update()
{
	Monster::Update();
}

void GiantSkullWarrior::Render()
{
	Monster::Render();
}
