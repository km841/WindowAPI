#include "pch.h"
#include "BelialHand.h"
#include "Animator.h"
#include "Texture.h"
#include "ResourceMgr.h"

BelialHand::BelialHand(BELIAL_HAND_TYPE _type)
	:mType(_type)
{
	mTex = ResourceMgr::GetInstance().Load<Texture>(L"BelialHand_Tex", L"Texture\\Belial_Hand_Anim.bmp");

	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	mIdleAnimName = L"BelialHandIdle";
	mAttAnimName = L"BelialHandAtt";

	GetAnimator()->RegisterAnimation(
		mIdleAnimName + L"Left",
		mTex,
		Vec2(0, 0),
		Vec2(171, 207),
		Vec2(171, 0),
		0.1f,
		10
	);

	GetAnimator()->RegisterAnimation(
		mIdleAnimName + L"Right",
		mTex,
		Vec2(0, 207),
		Vec2(171, 207),
		Vec2(171, 0),
		0.1f,
		10
	);

	GetAnimator()->RegisterAnimation(
		mAttAnimName + L"Left",
		mTex,
		Vec2(0, 0),
		Vec2(210, 240),
		Vec2(210, 0),
		0.1f,
		18
	);

	GetAnimator()->RegisterAnimation(
		mAttAnimName + L"Right",
		mTex,
		Vec2(0, 240),
		Vec2(210, 240),
		Vec2(210, 0),
		0.1f,
		18
	);

	switch (mType)
	{
	case BELIAL_HAND_TYPE::LEFT_HAND:
		GetAnimator()->SelectAnimation(mIdleAnimName + L"Left");
		break;
	case BELIAL_HAND_TYPE::RIGHT_HAND:
		GetAnimator()->SelectAnimation(mIdleAnimName + L"Right");
		break;
	}
}

BelialHand::~BelialHand()
{
}

void BelialHand::Initialize()
{
	GameObject::Initialize();
}

void BelialHand::Update()
{
	GameObject::Update();
}

void BelialHand::Render()
{
	GameObject::Render();
}

void BelialHand::Destroy()
{
	GameObject::Destroy();
}
