#include "pch.h"
#include "IceMage.h"
#include "Player.h"
#include "ResourceMgr.h"
#include "Texture.h"
#include "Animator.h"
#include "Animation.h"
#include "Collider.h"
#include "RigidBody.h"
#include "IceMageMissileEffect.h"

IceMage::IceMage()
{
	mToolID = TOOL_ID::BTN_ICE_MAGE;
	mMonType = MONSTER_TYPE::FLY_RANGE;
	//SetSize(Vec2(192.f, 192.f));

	GetCollider()->SetSize(Vec2(30.f, 30.f));
	GetCollider()->SetOffset(Vec2(0.f, -15.f));

	GetRigidBody()->SetMass(1.f);
	SetGravity(false);

	std::wstring idleAnimName = L"IceMage_Idle";
	SetIdleAnimName(idleAnimName);

	std::wstring moveAnimName = L"IceMage_Idle";
	SetMoveAnimName(moveAnimName);

	std::wstring attAnimName = L"IceMage_Att";
	SetAttAnimName(attAnimName);

	std::wstring attAfterAnimName = L"IceMage_Idle";
	SetAttAfterAnimName(attAfterAnimName);

	SetTraceStateAnimName(idleAnimName);
	SetPatrolStateAnimName(idleAnimName);
	SetAttStateAnimName(attAnimName);

	Texture* animTex = ResourceMgr::GetInstance().Load<Texture>(L"IceMageAnimTex", L"Texture\\Monster\\IceMageAnim.bmp");
	Texture* hitAnimTex = ResourceMgr::GetInstance().Load<Texture>(L"IceMageHitAnimTex", L"Texture\\Monster\\IceMageHitAnim.bmp");

	GetAnimator()->RegisterAnimation(
		idleAnimName + L"Left",
		animTex,
		Vec2(0.f, 0.f),
		Vec2(96.f, 90.f),
		Vec2(96.f, 0.f),
		0.1f,
		6
	);

	GetAnimator()->RegisterAnimation(
		idleAnimName + L"Right",
		animTex,
		Vec2(0.f, 90.f),
		Vec2(96.f, 90.f),
		Vec2(96.f, 0.f),
		0.1f,
		6
	);

	GetAnimator()->RegisterAnimation(
		attAnimName + L"Left",
		animTex,
		Vec2(0.f, 180.f),
		Vec2(96.f, 90.f),
		Vec2(96.f, 0.f),
		0.1f,
		12
	);

	GetAnimator()->RegisterAnimation(
		attAnimName + L"Right",
		animTex,
		Vec2(0.f, 270.f),
		Vec2(96.f, 90.f),
		Vec2(96.f, 0.f),
		0.1f,
		12
	);

	GetAnimator()->FindAnimation(idleAnimName + L"Left")->SetHitAnimation(hitAnimTex);
	GetAnimator()->FindAnimation(idleAnimName + L"Right")->SetHitAnimation(hitAnimTex);
	GetAnimator()->FindAnimation(attAnimName + L"Left")->SetHitAnimation(hitAnimTex);
	GetAnimator()->FindAnimation(attAnimName + L"Right")->SetHitAnimation(hitAnimTex);


	GetAnimator()->SelectAnimation(idleAnimName + L"Right", true);

	IceMageMissileEffect* effect = new IceMageMissileEffect;
	effect->SetOwner(this);
	SetEffect(effect);
}

IceMage::~IceMage()
{
}

void IceMage::Initialize()
{
	Monster::Initialize();
	mInfo.mSpeed = 0.f;
	mInfo.mAttDelay = 5.f;
}

void IceMage::Update()
{
	Monster::Update();
}

void IceMage::Render()
{
	Monster::Render();
}

void IceMage::Destroy()
{
	Monster::Destroy();
}

void IceMage::OnCollision(Collider* _other)
{
}

void IceMage::OnCollisionEnter(Collider* _other)
{
	Monster::OnCollisionEnter(_other);
}

void IceMage::OnCollisionExit(Collider* _other)
{
}

bool IceMage::Attack()
{
	return mEffect->Attack();
}

bool IceMage::DetectPlayer()
{
	Vec2 playerPos = Player::GetPlayer()->GetPos();
	Vec2 pos = GetPos();

	if ((playerPos - pos).Len() < 1000.f)
		return true;

	return false;
}

bool IceMage::DetectIntoAttRange()
{
	Vec2 playerPos = Player::GetPlayer()->GetPos();
	Vec2 pos = GetPos();

	if ((playerPos - pos).Len() < 1000.f)
		return true;

	return false;
}
