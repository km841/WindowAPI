#include "pch.h"
#include "BelialSword.h"
#include "Collider.h"
#include "Animator.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Animation.h"
#include "MonsterEffect.h"
#include "TimeMgr.h"
#include "CameraMgr.h"
#include "Player.h"
#include "Sound.h"

BelialSword::BelialSword()
	: mCreateFlag(false)
	, mChargeFlag(false)
	, mReadyFlag(false)
	, mCollision(false)
	, mChargeMaxTime(2.f)
	, mChargeCurTime(0.f)
	, mEffect(nullptr)
	, mChargeFrame(0)
	, mChargeAccTime(0.f)
	, mSpeed(1200.f)
	, mDeadMaxTime(2.0f)
	, mSwordSpawnSound(nullptr)
{
	mSwordSpawnSound = LOAD_SOUND(L"BelialSwordSpawn", L"Sound\\BelialSwordSpawn.wav");

	SetType(OBJECT_TYPE::MONSTER_EFFECT);
	CreateComponent(new Collider);
	GetCollider()->SetOwner(this);

	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	GetCollider()->SetSize(Vec2(30, 30));
	GetCollider()->SetOffset(Vec2(0, -15));

	Texture* swordTex = LOAD_TEXTURE(L"BelialSwordTex", L"Texture\\Monster\\Belial\\Belial_Sword.bmp");
	Texture* swordFXTex = LOAD_TEXTURE(L"BelialSwordFXTex", L"Texture\\Monster\\Belial\\Belial_Sword_FX.bmp");
	Texture* swordCreateDeadTex = LOAD_TEXTURE(L"BelialCreateDeadTex", L"Texture\\Monster\\Belial\\Belial_Sword_Create_Dead.bmp");
	Texture* swordChargeTex = LOAD_TEXTURE(L"BelialSwordChargeTex", L"Texture\\Monster\\Belial\\Belial_SwordAnim.bmp");

	GetAnimator()->RegisterAnimation(
		L"SwordAnim",
		swordTex,
		Vec2(0, 0),
		Vec2(195, 195),
		Vec2(195, 0),
		0.1f,
		1
	);

	GetAnimator()->RegisterAnimation(
		L"SwordFXAnim",
		swordFXTex,
		Vec2(0, 0),
		Vec2(210, 210),
		Vec2(210, 0),
		0.1f,
		1
	);

	GetAnimator()->RegisterAnimation(
		L"SwordCreateDeadAnim",
		swordCreateDeadTex,
		Vec2(0, 0),
		Vec2(105, 144),
		Vec2(105, 0),
		0.1f,
		3
	);

	mEffect = new MonsterEffect;
	mEffect->SetOwner(this);

	mEffect->CreateComponent(new Animator);
	mEffect->GetAnimator()->SetOwner(mEffect);

	mEffect->GetAnimator()->RegisterAnimation(
		L"BelialSwordChargeAnim",
		swordChargeTex,
		Vec2(0, 0),
		Vec2(63, 195),
		Vec2(63, 0),
		0.1f,
		8
	);

	mEffect->GetAnimator()->RegisterAnimation(
		L"BelialSwordStabbedAnim",
		swordChargeTex,
		Vec2(0, 195),
		Vec2(153, 66),
		Vec2(153, 0),
		0.1f,
		5
	);

	GetAnimator()->FindAnimation(L"SwordCreateDeadAnim")->SetOffset(Vec2(0, 60));
	GetAnimator()->SelectAnimation(L"SwordCreateDeadAnim", false);

	if (nullptr != mSwordSpawnSound)
	{
		mSwordSpawnSound->Play(false);
	}
}

BelialSword::~BelialSword()
{
	if (nullptr != mEffect)
	{
		delete mEffect;
		mEffect = nullptr;
	}
}

void BelialSword::Initialize()
{
	GameObject::Initialize();
}

void BelialSword::Update()
{
	GameObject::Update();

	if (false == mCreateFlag)
	{
		if (GetAnimator()->GetCurAnimation()->IsFinished())
		{
			mCreateFlag = true;
			
			// 플레이어 위치에 맞게 회전된 각도로 그려져야 함

			// 1. 칼 위치에서 1,0 벡터와 (플레이어 - 자신) 벡터간의 각도를 구한다
			// 2. 그만큼 회전시킨다.

			Vec2 playerPos = Player::GetPlayer()->GetPos();
			Vec2 curPos = GetPos();
			Vec2 dirVec = playerPos - curPos;
			mAngle = atan2(dirVec.y, dirVec.x);
			mAngle += PI / 2.f;
			GetAnimator()->RotSelectAnimation(L"SwordAnim", mAngle, true);
			mEffect->GetAnimator()->RotSelectAnimation(L"BelialSwordChargeAnim", mAngle, true);
			// 이펙트에게 Charge 애니메이션 지시
		}
	}

	if (false == mChargeFlag && true == mCreateFlag)
	{
		if (mChargeMaxTime < mChargeCurTime)
		{
			mChargeFlag = true;
		}

		else
		{
			mChargeCurTime += DT;
			Vec2 playerPos = Player::GetPlayer()->GetPos();
			Vec2 curPos = GetPos();
			Vec2 dirVec = playerPos - curPos;
			mAngle = atan2(dirVec.y, dirVec.x);
			mAngle += PI / 2.f;
			GetAnimator()->RotSelectAnimation(L"SwordAnim", mAngle, true);


			Animation* chargeAnim = mEffect->GetAnimator()->GetCurAnimation();
			if (nullptr != chargeAnim)
			{
				mChargeFrame = chargeAnim->GetCurFrame();
				mChargeAccTime = chargeAnim->GetAccTime();
			}
			mEffect->GetAnimator()->RotSelectAnimation(L"BelialSwordChargeAnim", mAngle, true);
			if (nullptr != chargeAnim)
			{
				mEffect->GetAnimator()->GetCurAnimation()->SetCurFrame(mChargeFrame);
				mEffect->GetAnimator()->GetCurAnimation()->SetAccTime(mChargeAccTime);
			}
			
			
			// 플레이어 위치에 따른 각도 변경

		}
	}

	if (true == mChargeFlag &&
		true == mCreateFlag)
	{
		if (false == IsDeadAnim() && false == mReadyFlag)
		{
			mEffect->GetAnimator()->RotSelectAnimation(L"BelialSwordChargeAnim", mAngle, false);
			mReadyFlag = true;
		}
		// 각도는 고정되고 플레이어를 향해 날아감

		else
		{
			if (false == mCollision)
			{
				if (mEffect->GetAnimator()->GetCurAnimation()->IsFinished())
				{

					GetAnimator()->RotSelectAnimation(L"SwordFXAnim", mAngle, true);
					if (mDir.IsZero())
					{
						mDir = Math::RotateVector(Vec2(0, -1), mAngle);
					}

					Vec2 curPos = GetPos();

					curPos += mDir * mSpeed * DT;
					SetPos(curPos);
				}
			}

			else
			{
				// 2초 있다가 Dead
				if (mDeadMaxTime < mDeadCurTime)
				{
					if (IsAlive())
					{
						GetAnimator()->SelectAnimation(L"SwordCreateDeadAnim", false);
						GetAnimator()->GetCurAnimation()->Reset();
						SetObjState(OBJECT_STATE::DEAD_ANIM);
					}

					else if (IsDeadAnim())
					{
						if (GetAnimator()->GetCurAnimation()->IsFinished())
						{
							SetObjState(OBJECT_STATE::DEAD);
						}
					}
				}
				else
				{
					mDeadCurTime += DT;
					GetAnimator()->RotSelectAnimation(L"SwordAnim", mAngle, true);
				}




				//GetAnimator()->SelectAnimation(L"SwordCreateDeadAnim", false);
			}
		}
	}

	if (nullptr != mEffect)
	{
		mEffect->Update();
	}

}

void BelialSword::Render()
{
	GameObject::Render();

	if (nullptr != mEffect)
	{
		mEffect->Render();
	}
}

void BelialSword::Destroy()
{
	GameObject::Destroy();

	if (nullptr != mEffect)
	{
		mEffect->Destroy();
	}
}

void BelialSword::OnCollision(Collider* _other)
{
}

void BelialSword::OnCollisionEnter(Collider* _other)
{
	if (OBJECT_TYPE::WALL == _other->GetOwner()->GetType())
	{
		mCollision = true;

	}
}

void BelialSword::OnCollisionExit(Collider* _other)
{
}

void BelialSword::Dead()
{
}
