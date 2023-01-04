#include "pch.h"
#include "CoinBullet.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "Sound.h"
#include "CameraMgr.h"
#include "EventRegisteror.h"
#include "Sound.h"

CoinBullet::CoinBullet()
	:mSound(nullptr)
	, mInvinMaxTime(0.02f)
	, mInvinCurTime(0.f)
	, mInvin(true)
{
	//mSound = LOAD_SOUND(L"CoinBulletHitSound", L"Sound\\CoinBulletHit.wav");

	GetCollider()->SetSize(Vec2(30.f, 30.f));
	GetCollider()->SetOffset(Vec2(0.f, -15.f));

	mInfo.mMinAtt = 5.f;
	mInfo.mMaxAtt = 10.f;
	mInfo.mSpeed = 1500.f;

	Texture* coinBulletTex = LOAD_TEXTURE(L"CoinBulletTex", L"Texture\\CoinGunAnim.bmp");
	Texture* coinBulletHitTex = LOAD_TEXTURE(L"CoinBulletHitTex", L"Texture\\RangeBallBullet.bmp");
	GetAnimator()->RegisterAnimation(
		L"CoinBullet",
		coinBulletTex,
		Vec2(0.f, 0.f),
		Vec2(32.f, 32.f),
		Vec2(32.f, 0.f),
		0.05f,
		8
	);

	GetAnimator()->RegisterAnimation(
		L"CoinBulletHit",
		coinBulletHitTex,
		Vec2(0.f, 42.f),
		Vec2(96.f, 96.f),
		Vec2(96.f, 0.f),
		0.05f,
		7
	);

	GetAnimator()->FindAnimation(L"CoinBulletHit")->SetEffectAnimation(true);
	GetAnimator()->SelectAnimation(L"CoinBullet", true);
}

CoinBullet::~CoinBullet()
{
}

void CoinBullet::Initialize()
{
}

void CoinBullet::Update()
{
	if (IsDeadAnim())
	{
		if (GetAnimator()->GetCurAnimation()->IsFinished())
		{
			SetObjState(OBJECT_STATE::DEAD);
			EventRegisteror::GetInstance().DeleteObject(this);	
		}
	}

	else
	{
		//화면 밖으로 날아가면 false
		if (CameraMgr::GetInstance().OutOfScreen(GetPos()))
		{
			SetObjState(OBJECT_STATE::DEAD_ANIM);
			GetAnimator()->SelectAnimation(L"CoinBulletHit", false);
		}

		if (mInvinMaxTime < mInvinCurTime)
		{
			mInvin = false;
		}

		else
		{
			mInvinCurTime += DT;
		}

		Vec2 bulletPos = GetPos();
		bulletPos += mDir * mInfo.mSpeed * DT;
		SetPos(bulletPos);
	}

	GameObject::Update();
}

void CoinBullet::Render()
{
	if (false == mInvin)
		GameObject::Render();
}

void CoinBullet::OnCollision(Collider* _other)
{
}

void CoinBullet::OnCollisionEnter(Collider* _other)
{
	if (OBJECT_TYPE::MONSTER == _other->GetOwner()->GetType() ||
		OBJECT_TYPE::WALL == _other->GetOwner()->GetType())
	{
		// 애니메이션 변경후 애니메이션이 끝나면 소멸
		SetObjState(OBJECT_STATE::DEAD_ANIM);
		GetAnimator()->SelectAnimation(L"CoinBulletHit", false);

		if (nullptr != mSound)
			mSound->Play(false);
	}
}

void CoinBullet::OnCollisionExit(Collider* _other)
{
}
