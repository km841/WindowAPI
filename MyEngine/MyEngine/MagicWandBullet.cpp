#include "pch.h"
#include "MagicWandBullet.h"
#include "Collider.h"
#include "Animation.h"
#include "Animator.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "CameraMgr.h"
#include "AfterImage.h"
#include "TimeMgr.h"

MagicWandBullet::MagicWandBullet()
	:mTarget(nullptr)
	,mAngle(0.f)
	,mMaxDuration(0.025f)
	,mCurDuration(0.f)
	,mInitMaxDuration(0.1f)
	,mInitCurDuration(0.f)
{
	GetCollider()->SetSize(Vec2(20.f, 20.f));
	GetCollider()->SetOffset(Vec2(0.f, -15.f));

	mInfo.mAtt = 10.f;
	mInfo.mSpeed = 500.f;

	Texture* laraBulletTex = ResourceMgr::GetInstance().Load<Texture>(L"LaraBulletAnim", L"Texture\\LaraBulletAnim.bmp");

	GetAnimator()->RegisterAnimation(
		L"LaraBullet",
		laraBulletTex,
		Vec2(0.f, 0.f),
		Vec2(42.f, 39.f),
		Vec2(42.f, 0.f),
		0.05f,
		4
	);

	GetAnimator()->RegisterAnimation(
		L"LaraBulletHit",
		laraBulletTex,
		Vec2(0.f, 39.f),
		Vec2(108.f, 105.f),
		Vec2(108.f, 0.f),
		0.05f,
		7
	);

	GetAnimator()->FindAnimation(L"LaraBullet")->SetEffectAnimation(true);
	GetAnimator()->SelectAnimation(L"LaraBullet", true);
}

MagicWandBullet::~MagicWandBullet()
{
}

void MagicWandBullet::Initialize()
{
}

void MagicWandBullet::Update()
{
	if (BULLET_STATE::DEAD_ANIM == GetBulletState())
	{
		if (GetAnimator()->GetCurAnimation()->IsFinished())
		{
			if (mAfterImages.empty())
			{
				SetBulletState(BULLET_STATE::DEAD);
			}
		}
	}

	else
	{
		 //화면 밖으로 날아가면 false
		if (CameraMgr::GetInstance().OutOfScreen(GetPos()))
		{
			SetBulletState(BULLET_STATE::DEAD_ANIM);
			GetAnimator()->SelectAnimation(L"LaraBulletHit", false);
		}

		if (mMaxDuration < mCurDuration && 
			BULLET_STATE::DEAD_ANIM != GetBulletState())
		{
			mCurDuration = 0.f;

			AfterImage* afterImg = new AfterImage;
			Animation* curAnim = GetAnimator()->FindAnimation(L"LaraBullet");
			int curFrame = curAnim->GetCurFrame();

			// 애니메이션과 프레임을 전달
			afterImg->SetAnimation(curAnim);
			afterImg->SetAnimFrame(curFrame);
			afterImg->SetPos(GetPos());

			mAfterImages.push_back(afterImg);
			
		}

		else if (mMaxDuration > mCurDuration)
		{
			mCurDuration += DT;
		}
		// n초에 한번씩

	}

	// dead 잔상 지워주기

	std::vector<AfterImage*>::iterator iter = mAfterImages.begin();
	for (; iter != mAfterImages.end();)
	{
		if (iter.operator*()->IsDead())
		{
			delete *iter;
			iter = mAfterImages.erase(iter);
		}

		else
		{
			iter.operator*()->Update();
			++iter;
		}
	}

	GameObject::Update();
}

void MagicWandBullet::Render()
{
	for (int i = 0; i < mAfterImages.size(); ++i)
	{
		mAfterImages[i]->Render();
	}

	GameObject::Render();
}

void MagicWandBullet::Destroy()
{
	for (int i = 0; i < mAfterImages.size(); ++i)
	{

		if (nullptr != mAfterImages[i])
		{
			delete mAfterImages[i];
			mAfterImages[i] = nullptr;
		}
	}
}

void MagicWandBullet::OnCollision(Collider* _other)
{
}

void MagicWandBullet::OnCollisionEnter(Collider* _other)
{
	if (OBJECT_TYPE::MONSTER == _other->GetOwner()->GetType())
	{
		// 애니메이션 변경후 애니메이션이 끝나면 소멸
		SetBulletState(BULLET_STATE::DEAD_ANIM);
		GetAnimator()->SelectAnimation(L"LaraBulletHit", false);
	}
}

void MagicWandBullet::OnCollisionExit(Collider* _other)
{
}
