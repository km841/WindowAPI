#include "pch.h"
#include "RotateMissileEffect.h"
#include "BatBullet.h"
#include "TimeMgr.h"
#include "Player.h"
#include "EventRegisteror.h"
#include "CameraMgr.h"
#include "Collider.h"
#include "Monster.h"
#include "Animation.h"
#include "Animator.h"

RotateMissileEffect::RotateMissileEffect()
	: mRadius(80.f)
	, mOmega(5.f)
	, mAngle(0.f)
	, mBulletInterval(0.05f)
	, mCurTime(0.f)
	, mMaxBullet(20)
	, mReady(false)
{
	mCoreBullet = new MonsterBullet;
}

RotateMissileEffect::~RotateMissileEffect()
{
	if (nullptr != mCoreBullet)
	{
		delete mCoreBullet;
		mCoreBullet = nullptr;
	}
}

void RotateMissileEffect::Initialize()
{
	MonsterMissileEffect::Initialize();
	Vec2 pos = GetPos();
	pos.y -= 80;
	mCoreBullet->SetPos(pos);
}

void RotateMissileEffect::Update()
{
	// Effect를 중심으로 회전한다.

	MonsterMissileEffect::Update();

	// 총알이 전부 스폰됐다면
	if (mReady)
	{
		// 충돌체 ON
		// 
		// 플레이어 방향으로 회전탄 발사
		for (int i = 0; i < mBullets.size(); ++i)
		{
			mBullets[i]->GetCollider()->SetEnable(true);
		}
		
		Vec2 coreBulletPos = mCoreBullet->GetPos();
		coreBulletPos.x += mPlayerVec.x * 200.f * DT;
		coreBulletPos.y += mPlayerVec.y * 200.f * DT;
		mCoreBullet->SetPos(coreBulletPos);

		if (mBullets.empty())
		{
			mReady = false;
		}
	}

	else
	{
		if (nullptr != mCoreBullet)
		{
			Vec2 pos = GetPos();
			pos.y -= 80;
			mCoreBullet->SetPos(pos);
		}
	}


	//총알이 비지 않았다면
	bool mBulletAlive = false;
	for (int i = 0; i < mBullets.size(); ++i)
	{
		if (IsAlive())
		{
			BatBullet* bullet = static_cast<BatBullet*>(mBullets[i]);
			float bulletAngle = bullet->GetAngle();
			bulletAngle += 180.f * DT;
			bullet->SetAngle(bulletAngle);

			float radian = Math::DegreeToRadian(bulletAngle);

			Vec2 bulletPos = mBullets[i]->GetPos();
			Vec2 coreBulletPos = mCoreBullet->GetPos();
			bulletPos.x = coreBulletPos.x + mRadius * cos(radian);
			bulletPos.y = coreBulletPos.y + mRadius * sin(radian);
			mBullets[i]->SetPos(bulletPos);

			mBulletAlive = true;
		}

		else if (IsDeadAnim())
			mBulletAlive = true;
	}

	// 시간이 지나면 초기화되도록 변경
	if (!mBullets.empty() && !mBulletAlive)
	{
		for (int i = 0; i < mBullets.size(); ++i)
		{
			EventRegisteror::GetInstance().DeleteObject(mBullets[i]);
		}
		mBullets.clear();

		mReady = false;
		mCurTime = 0.f;
		mPlayerVec = ZERO_VECTOR;
	}
}

void RotateMissileEffect::Render()
{
	mCoreBullet->Render();
}

void RotateMissileEffect::Destroy()
{
	for (int i = 0; i < mBullets.size(); ++i)
	{
		for (int i = 0; i < mBullets.size(); ++i)
		{
			EventRegisteror::GetInstance().DeleteObject(mBullets[i]);
		}
		mBullets.clear();
	}
}

bool RotateMissileEffect::Attack()
{
	// 특정 딜레이를 두고 n개를 생성시킨다.
	// 생성이 끝나면 그때부터 총알이 다 소멸할때까지
	// 소멸이 끝나면 공격 끝

	if (mMaxBullet > mBullets.size())
	{
		if (mBulletInterval < mCurTime)
		{
			mCurTime = 0.f;
			BatBullet* bullet = new BatBullet;
			bullet->GetCollider()->SetEnable(false);
			Vec2 coreBulletPos = mCoreBullet->GetPos();
			coreBulletPos.y -= mRadius;
			bullet->SetPos(coreBulletPos);
			mBullets.push_back(bullet);
			
			EventRegisteror::GetInstance().CreateObject(bullet, bullet->GetType());
		}

		else
		{
			mCurTime += DT;
		}


	}

	else
	{
		if (Vec2(0.f, 0.f) == mPlayerVec)
		{
			Vec2 coreBulletPos = mCoreBullet->GetPos();
			Vec2 playerPos = Player::GetPlayer()->GetPos();

			mPlayerVec = playerPos - coreBulletPos;
			mPlayerVec.Norm();

			mReady = true;
			return false;
		}
	}


	return true;

	// Bullet n개를 만든다
	// Bullet n개는 missileEffect를 중심으로 회전
	// n초 후에 플레이어 방향으로 발사됨
	// 중심이 되는 총알을 만들어야 함
	// 중심이 되는 총알이 이동함에 따라 나머지 총알도 같이 움직이게끔
}
