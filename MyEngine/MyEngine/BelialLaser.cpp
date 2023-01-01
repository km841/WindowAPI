#include "pch.h"
#include "BelialLaser.h"
#include "ResourceMgr.h"
#include "Texture.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"

BelialLaser::BelialLaser(BELIAL_LASER_TYPE _laserType, BELIAL_HAND_TYPE _handType)
	: mLaserType(_laserType)
	, mHandType(_handType)
{
	Texture* laserHeadTex = ResourceMgr::GetInstance().Load<Texture>(L"LaserHeadTex", L"Texture\\Monster\\Belial\\Belial_Laser_Head.bmp");
	Texture* laserBodyTex = ResourceMgr::GetInstance().Load<Texture>(L"LaserBodyTex", L"Texture\\Monster\\Belial\\Belial_Laser_Body.bmp");

	

	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);



	mLaserHeadAnimName = L"LaserHeadAnim";
	mLaserBodyAnimName = L"LaserBodyAnim";

	GetAnimator()->RegisterAnimation(
		mLaserHeadAnimName + L"Left",
		laserHeadTex,
		Vec2(0, 0),
		Vec2(96, 165),
		Vec2(96, 0),
		0.1f,
		7
	);

	GetAnimator()->RegisterAnimation(
		mLaserHeadAnimName + L"Right",
		laserHeadTex,
		Vec2(0, 165),
		Vec2(96, 165),
		Vec2(96, 0),
		0.1f,
		7
	);

	GetAnimator()->RegisterAnimation(
		mLaserBodyAnimName,
		laserBodyTex,
		Vec2(0, 0),
		Vec2(96, 165),
		Vec2(96, 0),
		0.1f,
		7
	);

	switch (mLaserType)
	{
	case BELIAL_LASER_TYPE::HEAD:
	{
		CreateComponent(new Collider);
		GetCollider()->SetOwner(this);

		GetCollider()->SetSize(Vec2(960, 100));

		switch (mHandType)
		{
		case BELIAL_HAND_TYPE::LEFT_HAND:
			GetAnimator()->SelectAnimation(mLaserHeadAnimName + L"Left", false);
			GetCollider()->SetOffset(Vec2(480, -80));
			break;

		case BELIAL_HAND_TYPE::RIGHT_HAND:
			GetAnimator()->SelectAnimation(mLaserHeadAnimName + L"Right", false);
			GetCollider()->SetOffset(Vec2(-480, -80));
			break;
		}
	}
		break;
	case BELIAL_LASER_TYPE::BODY:
		GetAnimator()->SelectAnimation(mLaserBodyAnimName, false);
		break;
	}

}

BelialLaser::~BelialLaser()
{
}

void BelialLaser::Update()
{
	GameObject::Update();

	Animation* curAnim = GetAnimator()->GetCurAnimation();
	if (nullptr != curAnim)
	{
		if (curAnim->IsFinished())
		{
			SetObjState(OBJECT_STATE::DEAD);
		}
	}
}

void BelialLaser::Render()
{
	GameObject::Render();
}
