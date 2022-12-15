#include "pch.h"
#include "MultipleMissileEffect.h"
#include "Player.h"
#include "BatBullet.h"
#include "TimeMgr.h"
#include "Monster.h"
#include "GiantBat.h"
#include "EventRegisteror.h"

MultipleMissileEffect::MultipleMissileEffect()
	: mMaxDuration(0.5f)
	, mCurDuration(mMaxDuration)
	, mAttCount(0.f)
{
}

MultipleMissileEffect::~MultipleMissileEffect()
{
}

void MultipleMissileEffect::Initialize()
{
	MonsterMissileEffect::Initialize();
}

void MultipleMissileEffect::Update()
{
	MonsterMissileEffect::Update();	
}

void MultipleMissileEffect::Render()
{

}

void MultipleMissileEffect::Destroy()
{
	//for (int i = 0; i < mBullets.size(); ++i)
	//{
	//	for (int i = 0; i < mBullets.size(); ++i)
	//	{
	//		EventRegisteror::GetInstance().DeleteObject(mBullets[i]);
	//	}
	//	mBullets.clear();
	//}
}

bool MultipleMissileEffect::Attack()
{
	// Attack에서는 생성하고 끝냄
	// 생성을 마쳤는지는 flag로 전달
	// for문을 돌며 시간간격에 따라  3번 발사함
	// 매 발사마다 특정 각도로 회전된 총알도 같이 발사
	// 공격까지 여기서 처리

	if (mBullets.empty())
	{
		Vec2 playerPos = Player::GetPlayer()->GetPos();
		Vec2 monsterPos = GetOwner()->GetPos();

		float radian = Math::DegreeToRadian(10.f);

		mDirs[0] = playerPos - monsterPos;
		mDirs[1] = Math::RotateVector(mDirs[0], -radian);
		mDirs[2] = Math::RotateVector(mDirs[0], radian);

		for (int i = 0; i < MULTIPLE_BULLET_1TIMES; ++i)
		{
			mDirs[i].Norm();
		}
	}

	// 현재 Bullet들을 방향에 맞게 이동시킴

	auto iter = mBullets.begin();
	for (; iter != mBullets.end(); )
	{
		BatBullet* bullet = static_cast<BatBullet*>(*iter);

		Vec2 dir = bullet->GetDir();
		Vec2 pos = bullet->GetPos();

		pos += dir * 200.f * DT;
		bullet->SetPos(pos);
		++iter;
	}

	if (mAttCount < MULTIPLE_BULLET_1TIMES)
	{
		if (mMaxDuration <= mCurDuration)
		{
			++mAttCount;
			mCurDuration = 0.f;
			for (int i = 0; i < MULTIPLE_BULLET_1TIMES; ++i)
			{
				BatBullet* bullet = new BatBullet;
				Vec2 pos = GetPos();
				pos.y -= 80.f;
				bullet->SetPos(pos);
				bullet->SetDir(mDirs[i % MULTIPLE_BULLET_1TIMES]);
				mBullets.push_back(bullet);

				EventRegisteror::GetInstance().CreateObject(bullet, bullet->GetType());
			}
		}
		else
		{
			mCurDuration += DT;
		}

		return true;
	}

	else
	{
		bool bulletAlive = false;
		for (int i = 0; i < mBullets.size(); ++i)
		{
			if (BULLET_STATE::ALIVE == mBullets[i]->GetBulletState() || 
				BULLET_STATE::DEAD_ANIM == mBullets[i]->GetBulletState())
			{
				bulletAlive = true;
			}
		}

		if (false == bulletAlive)
		{
			for (int i = 0; i < mBullets.size(); ++i)
			{
				EventRegisteror::GetInstance().DeleteObject(mBullets[i]);
			}

			mBullets.clear();
			mAttCount = 0.f;
			mCurDuration = mMaxDuration;

			for (int i = 0; i < MULTIPLE_BULLET_1TIMES; ++i)
			{
				mDirs[i] = ZERO_VECTOR;
			}
		}

		return bulletAlive;
	}
}
