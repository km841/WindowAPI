#include "pch.h"
#include "GiantSkullWarrior.h"
#include "Collider.h"
#include "Animator.h"
#include "RigidBody.h"
#include "Texture.h"
#include "ResourceMgr.h"

GiantSkullWarrior::GiantSkullWarrior()
{
	SetSize(Vec2(99.f, 90.f));

	GetCollider()->SetSize(Vec2(30.f, 30.f));
	GetCollider()->SetOffset(Vec2(0.f, -15.f));

	GetRigidBody()->SetMass(1.f);

	std::wstring idleAnimName = L"GiantSkull_Idle";
	SetIdleAnimName(idleAnimName);

	std::wstring walkAnimName = L"GiantSkull_Walk";
	SetWalkAnimName(walkAnimName);



	

	
	Texture* animTex = ResourceMgr::GetInstance().Load<Texture>(L"GiantSkullAnimTex", L"Texture\\giant_skull_animation.bmp");

	GetAnimator()->RegisterAnimation(
		L"GiantSkull_IdleLeft",
		animTex,
		Vec2(0.f, 0.f),
		Vec2(33.f, 30.f),
		Vec2(33.f, 0.f),
		0.1f,
		6
	);

	GetAnimator()->RegisterAnimation(
		L"GiantSkull_IdleRight",
		animTex,
		Vec2(0.f, 30.f),
		Vec2(33.f, 30.f),
		Vec2(33.f, 0.f),
		0.1f,
		6
	);

	GetAnimator()->RegisterAnimation(
		L"GiantSkull_WalkLeft",
		animTex,
		Vec2(0.f, 60.f),
		Vec2(33.f, 30.f),
		Vec2(33.f, 0.f),
		0.1f,
		6
	);

	GetAnimator()->RegisterAnimation(
		L"GiantSkull_WalkRight",
		animTex,
		Vec2(0.f, 90.f),
		Vec2(33.f, 30.f),
		Vec2(33.f, 0.f),
		0.1f,
		6
	);

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
