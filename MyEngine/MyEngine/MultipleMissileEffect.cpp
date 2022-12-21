#include "pch.h"
#include "MultipleMissileEffect.h"
#include "Player.h"
#include "BatBullet.h"
#include "TimeMgr.h"
#include "Monster.h"
#include "GiantBat.h"
#include "EventRegisteror.h"
#include "Animation.h"
#include "Animator.h"

MultipleMissileEffect::MultipleMissileEffect()
	: mMaxDuration(0.3f)
	, mCurDuration(mMaxDuration)
	, mAttCount(0.f)
	, mMaxStayDuration(2.0f)
	, mStayDuration(0.f)
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
	//bool bulletAlive = false;
	//for (int i = 0; i < mBullets.size(); ++i)
	//{
	//	if (mBullets[i]->IsAlive() ||
	//		mBullets[i]->IsDeadAnim())
	//	{
	//		BatBullet* bullet = static_cast<BatBullet*>(mBullets[i]);

	//		Vec2 dir = bullet->GetDir();
	//		Vec2 pos = bullet->GetPos();

	//		pos += dir * 200.f * DT;
	//		bullet->SetPos(pos);

	//		bulletAlive = true;
	//	}
	//}

	//if (!mBullets.empty() && !bulletAlive)
	//{
	//	for (int i = 0; i < mBullets.size(); ++i)
	//	{
	//		EventRegisteror::GetInstance().DeleteObject(mBullets[i]);
	//	}

	//	mBullets.clear();
	//	mAttCount = 0.f;
	//	mCurDuration = mMaxDuration;

	//	for (int i = 0; i < MULTIPLE_BULLET_1TIMES; ++i)
	//	{
	//		mDirs[i] = ZERO_VECTOR;
	//	}
	//}


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
	// Attack������ �����ϰ� ����
	// ������ ���ƴ����� flag�� ����
	// for���� ���� �ð����ݿ� ����  3�� �߻���
	// �� �߻縶�� Ư�� ������ ȸ���� �Ѿ˵� ���� �߻�

	if (0.f == mAttCount)
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

	// ���� Bullet���� ���⿡ �°� �̵���Ŵ



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
				bullet->SetBulletWayType(BULLET_WAY_TYPE::LINEAR);

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
		mAttCount = 0.f;
		return false;
	}
}
