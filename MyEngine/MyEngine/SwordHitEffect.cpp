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

	Texture* animTex = ResourceMgr::GetInstance().Load<Texture>(L"SwordHitTex", L"Texture\\sword_hit.bmp");

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

			// ���Ϳ� �浹�� �߻����� ��
			// ���� Dummy�� �ִٸ� �� ���̿��� ������ ��ǥ�� �����ְ� �ִϸ��̼� �����ϱ�
			// ���̰� ���� �ִٴ°� ��� �Ǻ�?
			// ������ ���� �ִϸ��̼��� ���������� Ȯ���ϰ� �����ٸ� ���°���
			// �ʱⰪ�� �־��? ó���� nullptr�̴ϱ�..

			Animation* curAnim = mHitDummy[i]->GetAnimator()->GetCurAnimation();
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
			
			if (nullptr == curAnim)
			{
				mHitDummy[i]->SetPos(otherPos);
				mHitDummy[i]->GetAnimator()->RotSelectAnimation(L"SwordHitAnim", mAngle, false);
				break;
			}

			else 
			{
				// nullptr�� �ƴ� ���.. �׷��� �ִϸ����Ϳ� rot�� �����Ű� �װ� finished������ Ȯ���ؼ� ó�����ָ� �ɵ�

				Animation* anim = mHitDummy[i]->GetAnimator()->FindAnimation(L"SwordHitAnimRot");

				if (anim->IsFinished())
				{
					// �ش� ������ �´� �ִϸ��̼��� ����� ����Ѵ�
					mHitDummy[i]->SetPos(otherPos);
					mHitDummy[i]->GetAnimator()->RotSelectAnimation(L"SwordHitAnim", mAngle, false);
					break;
				}	
			}
		}
	}
	
}

void SwordHitEffect::OnCollisionExit(Collider* _other)
{
}
