#include "pch.h"
#include "SwordHitEffect.h"
#include "Animator.h"
#include "Collider.h"
#include "ResourceMgr.h"
#include "Texture.h"
#include "Animator.h"
#include "Animation.h"

SwordHitEffect::SwordHitEffect()
{
	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	Texture* animTex = LOAD_TEXTURE(L"SwordHitTex", L"Texture\\sword_hit.bmp");

	for (int i = 0; i < HIT_MAX; ++i)
	{
		mHitDummy[i] = new GameObject;
		mHitDummy[i]->CreateComponent(new Animator);
		mHitDummy[i]->GetAnimator()->SetOwner(mHitDummy[i]);

		mHitDummy[i]->GetAnimator()->RegisterAnimation(
			L"SwordHitAnim",
			animTex,
			Vec2(0, 0),
			Vec2(126, 126),
			Vec2(126, 0),
			0.07f,
			4
		);
	}
	
	CreateComponent(new Collider);
	GetCollider()->SetOwner(this);
}

SwordHitEffect::~SwordHitEffect()
{
	for (int i = 0; i < HIT_MAX; ++i)
	{
		if (nullptr != mHitDummy[i])
		{
			delete mHitDummy[i];
			mHitDummy[i] = nullptr;
		}

	}
}

void SwordHitEffect::Update()
{
	Effect::Update();

	for (int i = 0; i < HIT_MAX; ++i)
	{
		if (nullptr != mHitDummy[i])
		{
			mHitDummy[i]->Update();
		}
	}
}

void SwordHitEffect::Render()
{
	Effect::Render();

	for (int i = 0; i < HIT_MAX; ++i)
	{
		if (nullptr != mHitDummy[i])
		{
			mHitDummy[i]->Render();
		}
	}
}

void SwordHitEffect::OnCollision(Collider* _other)
{
}

void SwordHitEffect::OnCollisionEnter(Collider* _other)
{
	if (OBJECT_TYPE::MONSTER == _other->GetOwner()->GetType())
	{
		for (int i = 0; i < HIT_MAX; ++i)
		{

			// 몬스터와 충돌이 발생했을 때
			// 쉬는 Dummy가 있다면 그 더미에게 몬스터의 좌표를 던져주고 애니메이션 실행하기
			// 더미가 쉬고 있다는걸 어떻게 판별?
			// 더미의 현재 애니메이션이 끝났는지를 확인하고 끝났다면 쉬는거임
			// 초기값이 있어야? 처음엔 nullptr이니까..

			
			int randomOffset = 1 + (rand() % 20);
			int randomSign = rand() % 2;
			int randomXY = rand() % 2;

			Vec2 otherPos = _other->GetPos();
			randomSign = randomSign == 0 ? -1 : 1;
			randomOffset = randomOffset * randomSign;

			if (randomXY == 0)
			{
				otherPos.y += randomOffset;
			}
			else
			{
				otherPos.x += randomOffset;
			}
			Animation* curAnim = mHitDummy[i]->GetAnimator()->GetCurAnimation();

			if (nullptr == curAnim)
			{
				mHitDummy[i]->SetPos(otherPos);
				mHitDummy[i]->GetAnimator()->RotSelectAnimation(L"SwordHitAnim", mAngle, false);
				mHitDummy[i]->GetAnimator()->GetCurAnimation()->Reset();
				break;
			}

			else
			{
				if (curAnim->IsFinished())
				{
					mHitDummy[i]->SetPos(otherPos);
					mHitDummy[i]->GetAnimator()->RotSelectAnimation(L"SwordHitAnim", mAngle, false);
					mHitDummy[i]->GetAnimator()->GetCurAnimation()->Reset();
					break;
				}
			}

		}
	}
	
}

void SwordHitEffect::OnCollisionExit(Collider* _other)
{
}
