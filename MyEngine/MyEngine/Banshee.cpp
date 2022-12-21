#include "pch.h"
#include "Banshee.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Animator.h"
#include "Animation.h"
#include "ResourceMgr.h"
#include "Texture.h"
#include "CameraMgr.h"
#include "BansheeMissileEffect.h"
#include "Player.h"

Banshee::Banshee()
{
	mInfo.mSpeed = 0.f;
	mMonType = MONSTER_TYPE::FLY_RANGE;
	//SetSize(Vec2(192.f, 192.f));

	GetCollider()->SetSize(Vec2(30.f, 30.f));
	GetCollider()->SetOffset(Vec2(0.f, -50.f));

	GetRigidBody()->SetMass(1.f);
	SetGravity(false);

	std::wstring idleAnimName = L"Banshee_Idle";
	SetIdleAnimName(idleAnimName);

	std::wstring moveAnimName = L"Banshee_Idle";
	SetMoveAnimName(moveAnimName);

	std::wstring attAnimName = L"Banshee_Att";
	SetAttAnimName(attAnimName);

	std::wstring attAfterAnimName = L"Banshee_Idle";
	SetAttAfterAnimName(attAfterAnimName);

	Texture* animTex = ResourceMgr::GetInstance().Load<Texture>(L"BansheeAnimTex", L"Texture\\BansheeAnim.bmp");

	GetAnimator()->RegisterAnimation(
		idleAnimName + L"Left",
		animTex,
		Vec2(0.f, 0.f),
		Vec2(60.f, 66.f),
		Vec2(60.f, 0.f),
		0.1f,
		6
	);

	GetAnimator()->RegisterAnimation(
		idleAnimName + L"Right",
		animTex,
		Vec2(0.f, 0.f),
		Vec2(60.f, 66.f),
		Vec2(60.f, 0.f),
		0.1f,
		6
	);

	GetAnimator()->RegisterAnimation(
		attAnimName + L"Left",
		animTex,
		Vec2(0.f, 66.f),
		Vec2(60.f, 66.f),
		Vec2(60.f, 0.f),
		0.1f,
		6
	);

	GetAnimator()->RegisterAnimation(
		attAnimName + L"Right",
		animTex,
		Vec2(0.f, 66.f),
		Vec2(60.f, 66.f),
		Vec2(60.f, 0.f),
		0.1f,
		6
	);


	GetAnimator()->SelectAnimation(idleAnimName + L"Right", true);

	BansheeMissileEffect* effect = new BansheeMissileEffect;
	effect->SetOwner(this);
	SetEffect(effect);
}

Banshee::~Banshee()
{
}

void Banshee::Initialize()
{
	Monster::Initialize();
}

void Banshee::Update()
{
	Monster::Update();
}

void Banshee::Render()
{
	Monster::Render();
}

void Banshee::Destroy()
{
	Monster::Destroy();
}

void Banshee::OnCollision(Collider* _other)
{
}

void Banshee::OnCollisionEnter(Collider* _other)
{
	Monster::OnCollisionEnter(_other);
}

void Banshee::OnCollisionExit(Collider* _other)
{
}

bool Banshee::Attack()
{
	return mEffect->Attack();
}

bool Banshee::DetectPlayer()
{
	Vec2 playerPos = Player::GetPlayer()->GetPos();
	Vec2 pos = GetPos();

	if ((playerPos - pos).Len() < 1000.f)
		return true;

	return false;
}

bool Banshee::DetectIntoAttRange()
{
	Vec2 playerPos = Player::GetPlayer()->GetPos();
	Vec2 pos = GetPos();

	if ((playerPos - pos).Len() < 1000.f)
		return true;

	return false;
}
