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
#include "SceneMgr.h"
#include "Scene.h"
#include "Player.h"
#include "Monster.h"
#include "EventRegisteror.h"

MagicWandBullet::MagicWandBullet()
	:mTarget(nullptr)
	,mAngle(0.f)
	,mMaxDuration(0.025f)
	,mCurDuration(0.f)
	,mInitMaxDuration(0.1f)
	,mInitCurDuration(0.f)
	,mAngleLimit(Math::DegreeToRadian(3.f))
{
	GetCollider()->SetSize(Vec2(20.f, 20.f));
	GetCollider()->SetOffset(Vec2(0.f, -15.f));

	mInfo.mAtt = 10.f;
	mInfo.mSpeed = 750.f;

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
	if (IsDeadAnim())
	{
		if (GetAnimator()->GetCurAnimation()->IsFinished())
		{
			if (mAfterImages.empty())
			{
				SetObjState(OBJECT_STATE::DEAD);
				EventRegisteror::GetInstance().DeleteObject(this);
			}
		}
	}

	else
	{
		//화면 밖으로 날아가면 false
		if (CameraMgr::GetInstance().OutOfScreen(GetPos()))
		{
			SetObjState(OBJECT_STATE::DEAD_ANIM);
			GetAnimator()->SelectAnimation(L"LaraBulletHit", false);
		}

		MoveUpdate();
	}
	// dead 잔상 지워주기
	AfterImageUpdate();
	GameObject::Update();
}

void MagicWandBullet::Render()
{

	AfterImageRender();
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
		SetObjState(OBJECT_STATE::DEAD_ANIM);
		GetAnimator()->SelectAnimation(L"LaraBulletHit", false);
	}
}

void MagicWandBullet::OnCollisionExit(Collider* _other)
{
}

void MagicWandBullet::MoveUpdate()
{
	if (mMaxDuration < mCurDuration &&
		!IsDeadAnim())
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

	else
	{
		mCurDuration += DT;
		Vec2 bulletPos = GetPos();
		Vec2 dir = GetBulletVec();

		bulletPos += dir * mInfo.mSpeed * DT;
		mSpeedVector = dir;
		SetPos(bulletPos);
	}
}

void MagicWandBullet::AfterImageUpdate()
{
	std::vector<AfterImage*>::iterator iter = mAfterImages.begin();
	for (; iter != mAfterImages.end();)
	{
		if (iter.operator*()->IsDead())
		{
			delete* iter;
			iter = mAfterImages.erase(iter);
		}

		else
		{
			iter.operator*()->Update();
			++iter;
		}
	}
}

void MagicWandBullet::AfterImageRender()
{
	for (int i = 0; i < mAfterImages.size(); ++i)
	{
		mAfterImages[i]->Render();
	}
}

Vec2 MagicWandBullet::GetBulletVec()
{
	Vec2 dir = mSpeedVector;
	if (dir.IsZero())
	{
		dir = mInitDir;
	}

	Vec2 bulletPos = GetPos();

	if (mMaxDuration > mCurDuration)
	{
		mCurDuration += DT;
		mSpeedVector = mInitDir;
	}

	if (nullptr == mTarget)
	{
		GameObject* target =
			SceneMgr::GetInstance().GetCurScene()->GetNearestObject(Player::GetPlayer(), OBJECT_TYPE::MONSTER);

		if (nullptr != target)
		{
			mTarget = target;
		}
	}

	else
	{
		if (mTarget->IsDead())
		{
			GameObject* target =
				SceneMgr::GetInstance().GetCurScene()->GetNearestObject(Player::GetPlayer(), OBJECT_TYPE::MONSTER);

			if (nullptr != target)
			{
				mTarget = target;
			}

			else
			{
				return dir;
			}
		}

		else
		{
			Vec2 targetPos = mTarget->GetCollider()->GetPos();
			Vec2 targetVec = targetPos - bulletPos;

			float curAngle = atan2(dir.y, dir.x);
			float targetAngle = atan2(targetVec.y, targetVec.x);
			float distance = targetVec.Len();

			if (distance > WINDOW_WIDTH_SIZE * 0.75f)
			{
				dir += targetVec;
				dir.Norm();
			}

			else if (curAngle > targetAngle)
			{
				if (curAngle - targetAngle > mAngleLimit)
				{
					dir = Math::RotateVector(dir, -mAngleLimit);
				}

				else
				{
					dir = Math::RotateVector(dir, -(curAngle - targetAngle));
				}
			}

			else if (curAngle < targetAngle)
			{
				if (targetAngle - curAngle > mAngleLimit)
				{
					dir = Math::RotateVector(dir, mAngleLimit);
				}

				else
				{
					dir = Math::RotateVector(dir, (targetAngle - curAngle));
				}
			}
		}

	}


	return dir;
}

