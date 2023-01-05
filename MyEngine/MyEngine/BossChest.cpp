#include "pch.h"
#include "BossChest.h"
#include "KeyMgr.h"
#include "Gold.h"
#include "GoldBar.h"
#include "Coin.h"
#include "ResourceMgr.h"
#include "TimeMgr.h"
#include "RigidBody.h"
#include "Collider.h"

BossChest::BossChest()
	: mMaxTime(2.f)
	, mCurTime(0.f)
	, mDropMaxTime(0.3f)
	, mDropCurTime(0.f)
	, mComplete(false)
{
	mOpenedTex = LOAD_TEXTURE(L"BossChestOpenedTex", L"Texture\\BossTresureOpened.bmp");
	mClosedTex = LOAD_TEXTURE(L"BossChestClosedTex", L"Texture\\BossTresureClosed.bmp");

	CreateComponent(new RigidBody);
	GetRigidBody()->SetOwner(this);
	GetRigidBody()->SetMass(1.f);

	SetGround(false);
}

BossChest::~BossChest()
{
}

void BossChest::Initialize()
{
}

void BossChest::Update()
{
	GameObject::Update();

	if (CHEST_STATE::CLOSE == mState &&
		IS_JUST_PRESSED(KEY::F))
	{
		mState = CHEST_STATE::OPEN;
		// Item Drop

		int billion = mMoney / 100;
		int changes = mMoney % 100;
		int coin = changes / 10;

		Vec2 dropPos = GetPos();
		dropPos.y -= 30.f;

		for (int i = 0; i < billion; ++i)
		{
			int randomAngle = 250 + (rand() % 40);
			Gold::Drop(new GoldBar, dropPos, 100, (float)randomAngle);
		}

		for (int i = 0; i < coin; ++i)
		{
			int randomAngle = 250 + (rand() % 40);
			Gold::Drop(new Coin, dropPos, 10, (float)randomAngle);
		}

	}

	if (CHEST_STATE::OPEN == mState)
	{
		if (false == mComplete)
		{
			if (mMaxTime < mCurTime)
			{
				mComplete = true;

			}

			else
			{
				mCurTime += DT;

				if (mDropMaxTime < mDropCurTime)
				{
					mDropCurTime = 0.f;
					int billion = mMoney / 100;
					int changes = mMoney % 100;
					int coin = changes / 10;

					Vec2 dropPos = GetPos();
					dropPos.y -= 30.f;

					for (int i = 0; i < billion; ++i)
					{
						int randomAngle = 250 + (rand() % 40);
						Gold::Drop(new GoldBar, dropPos, 100, (float)randomAngle);
					}

					for (int i = 0; i < coin; ++i)
					{
						int randomAngle = 250 + (rand() % 40);
						Gold::Drop(new Coin, dropPos, 10, (float)randomAngle);
					}
				}

				else
				{
					mDropCurTime += DT;
				}
		}


		}
	}
}

void BossChest::Render()
{
	Chest::Render();
}

void BossChest::Destroy()
{
}

void BossChest::OnCollision(Collider* _other)
{
	Chest::OnCollision(_other);
}

void BossChest::OnCollisionEnter(Collider* _other)
{
	if (OBJECT_TYPE::WALL == _other->GetOwner()->GetType() ||
		OBJECT_TYPE::FOOTHOLD == _other->GetOwner()->GetType() )
	{
		GetRigidBody()->SetVelocity_Y_Zero();
		SetGround(true);
	}
}

void BossChest::OnCollisionExit(Collider* _other)
{
	Chest::OnCollisionExit(_other);
}
