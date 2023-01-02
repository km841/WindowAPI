#include "pch.h"
#include "BelialHand.h"
#include "Animator.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Animation.h"
#include "BelialLaser.h"
#include "EventRegisteror.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "Player.h"
#include "Sound.h"
int BelialHand::laserCount = 0;
BelialHand::BelialHand(BELIAL_HAND_TYPE _type)
	: mType(_type)
	, mAttFlag(false)
	, mAttacked(false)
	, mStayMaxTime(0.5f)
	, mStayCurTime(0.f)
	, mLaserBodyCount(12)
	, mDistance(0.f)
	, mSpeed(0.f)
	, mSound(nullptr)
{
	
	mSound = LOAD_SOUND(L"LaserShot", L"Sound\\BelialLaser.wav");
	mTex = LOAD_TEXTURE(L"BelialHand_Tex", L"Texture\\Monster\\Belial\\Belial_Hand_Anim.bmp");

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
		0.05f,
		10
	);

	GetAnimator()->RegisterAnimation(
		mIdleAnimName + L"Right",
		mTex,
		Vec2(0, 207),
		Vec2(171, 207),
		Vec2(171, 0),
		0.05f,
		10
	);

	GetAnimator()->RegisterAnimation(
		mAttAnimName + L"Left",
		mTex,
		Vec2(0, 414),
		Vec2(210, 240),
		Vec2(210, 0),
		0.05f,
		18
	);

	GetAnimator()->RegisterAnimation(
		mAttAnimName + L"Right",
		mTex,
		Vec2(0, 654),
		Vec2(210, 240),
		Vec2(210, 0),
		0.05f,
		18
	);

	GetAnimator()->FindAnimation(mIdleAnimName + L"Left")->SetTransMode(true, 3.0f, TRANS_MODE::FADE_IN);
	GetAnimator()->FindAnimation(mIdleAnimName + L"Right")->SetTransMode(true, 3.0f, TRANS_MODE::FADE_IN);
	GetAnimator()->FindAnimation(mAttAnimName + L"Left")->SetOffset(Vec2(0, 30));
	GetAnimator()->FindAnimation(mAttAnimName + L"Right")->SetOffset(Vec2(0, 30));

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

	for (int i = 0; i < mLasers.size(); ++i)
	{
		if (nullptr != mLasers[i])
		{
			delete mLasers[i];
			mLasers[i] = nullptr;
		}
	}
}

bool BelialHand::Skill()
{
	// void������ �׳� �߻�?
	// LaserType�� ���� �ִϸ��̼� �ٸ��� ����
	
	// �ڱ� ��ġ + Offset�����ӹ�ġ

	if (false == mAttFlag)
	{
		mAttFlag = true;

		switch (mType)
		{
		case BELIAL_HAND_TYPE::LEFT_HAND:
			GetAnimator()->SelectAnimation(mAttAnimName + L"Left", false);
			break;

		case BELIAL_HAND_TYPE::RIGHT_HAND:
			GetAnimator()->SelectAnimation(mAttAnimName + L"Right", false);
			break;
		}

		Player* player = Player::GetPlayer();
		if (nullptr != player)
		{
			Vec2 playerPos = player->GetPos();
			playerPos.y += 15.f;
			Vec2 curPos = GetPos();
			mDistance = playerPos.y - curPos.y;

			if (0.f > mDistance)
			{
				mDir = Vec2(0, -1);
				mDistance = -mDistance;
			}

			else
			{
				mDir = Vec2(0, 1);
			}

			mSpeed = mDistance / (mStayMaxTime / 2.f);
		}

	}

	else
	{
		if (mStayMaxTime < mStayCurTime)
		{
			Animation* curAnim = GetAnimator()->GetCurAnimation();
			if (nullptr != curAnim)
			{
				if (curAnim->IsFinished())
				{
					curAnim->Reset();

					switch (mType)
					{
					case BELIAL_HAND_TYPE::LEFT_HAND:
						GetAnimator()->SelectAnimation(mIdleAnimName + L"Left");
						break;
					case BELIAL_HAND_TYPE::RIGHT_HAND:
						GetAnimator()->SelectAnimation(mIdleAnimName + L"Right");
						break;
					}

					for (int i = 0; i < mLasers.size(); ++i)
					{
						if (nullptr != mLasers[i])
						{
							if (BELIAL_LASER_TYPE::HEAD == mLasers[i]->GetLaserType())
							{
								mLasers[i]->GetCollider()->SetEnable(false);
							}
						}
					}


					mStayCurTime = 0.f;
					mAttFlag = false;
					mAttacked = false;
					return false;
				}
			}


			if (false == mAttacked)
			{
				mAttacked = true;
				Vec2 curPos = GetPos();

				switch (mType)
				{
				case BELIAL_HAND_TYPE::LEFT_HAND:
					curPos += Vec2(30.f, 5.f);
					break;

				case BELIAL_HAND_TYPE::RIGHT_HAND:
					curPos += Vec2(-30.f, 5.f);
					break;
				}

				BelialLaser* laserHead = new BelialLaser(BELIAL_LASER_TYPE::HEAD, mType);
				laserHead->SetPos(curPos);

				mLasers.push_back(laserHead);
				EventRegisteror::GetInstance().CreateObject(laserHead, laserHead->GetType());


				for (int i = 0; i < mLaserBodyCount; ++i)
				{
					switch (mType)
					{
					case BELIAL_HAND_TYPE::LEFT_HAND:
						curPos.x += 96.f;
						break;

					case BELIAL_HAND_TYPE::RIGHT_HAND:
						curPos.x -= 96.f;
						break;
					}


					BelialLaser* laserBody = new BelialLaser(BELIAL_LASER_TYPE::BODY, mType);
					laserBody->SetPos(curPos);

					mLasers.push_back(laserBody);
					EventRegisteror::GetInstance().CreateObject(laserBody, laserBody->GetType());

					if (nullptr != mSound)
					{
						mSound->Play(false);
					}
				}
			}

		}

		else
		{
			mStayCurTime += DT;

			if (mStayCurTime < (mStayMaxTime / 2.f))
			{
				// �÷��̾� ���� �����̱�
				Vec2 curPos = GetPos();
				curPos += mDir * mSpeed * DT;
				SetPos(curPos);
			}
		}


	}


	return true;
}

void BelialHand::Dead()
{
	switch (mType)
	{
	case BELIAL_HAND_TYPE::LEFT_HAND:
		GetAnimator()->SelectAnimation(mIdleAnimName + L"Left");
		break;
	case BELIAL_HAND_TYPE::RIGHT_HAND:
		GetAnimator()->SelectAnimation(mIdleAnimName + L"Right");
		break;
	}

	GetAnimator()->GetCurAnimation()->Reset();
	GetAnimator()->GetCurAnimation()->SetFrameFix(true);
}
