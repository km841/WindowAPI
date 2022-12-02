#include "pch.h"
#include "GiantBat.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Animator.h"
#include "Animation.h"
#include "ResourceMgr.h"
#include "Texture.h"

GiantBat::GiantBat()
{
	SetSize(Vec2(99.f, 90.f));

	GetCollider()->SetSize(Vec2(30.f, 30.f));
	GetCollider()->SetOffset(Vec2(0.f, -15.f));

	GetRigidBody()->SetMass(1.f);
	SetGround(false);

	std::wstring idleAnimName = L"GiantBat_Idle";
	SetIdleAnimName(idleAnimName);

	std::wstring moveAnimName = L"GiantBat_Move";
	SetMoveAnimName(moveAnimName);

	std::wstring attAnimName = L"GiantBat_Att";
	SetAttAnimName(attAnimName);

	Texture* animTex = ResourceMgr::GetInstance().Load<Texture>(L"GiantBatAnimTex", L"Texture\\giant_bat_animation.bmp");

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


	GetAnimator()->SelectAnimation(L"GiantBat_IdleLeft", true);
}

GiantBat::~GiantBat()
{
}

void GiantBat::Initialize()
{
	Monster::Initialize();
}

void GiantBat::Update()
{
	Monster::Update();
}

void GiantBat::Render()
{
	Monster::Render();
}

void GiantBat::Destroy()
{
	Monster::Destroy();
}

void GiantBat::OnCollision(Collider* _other)
{
}

void GiantBat::OnCollisionEnter(Collider* _other)
{
}

void GiantBat::OnCollisionExit(Collider* _other)
{
}

bool GiantBat::Attack()
{
	return false;
}
