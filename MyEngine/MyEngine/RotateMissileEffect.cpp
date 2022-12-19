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
	// Effect�� �߽����� ȸ���Ѵ�.

	MonsterMissileEffect::Update();

	// �Ѿ��� ���� �����ƴٸ�
	if (mReady)
	{
		// �浹ü ON
		// 
		// �÷��̾� �������� ȸ��ź �߻�
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


	//�Ѿ��� ���� �ʾҴٸ�
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

	// �ð��� ������ �ʱ�ȭ�ǵ��� ����
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
	// Ư�� �����̸� �ΰ� n���� ������Ų��.
	// ������ ������ �׶����� �Ѿ��� �� �Ҹ��Ҷ�����
	// �Ҹ��� ������ ���� ��

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

	// Bullet n���� �����
	// Bullet n���� missileEffect�� �߽����� ȸ��
	// n�� �Ŀ� �÷��̾� �������� �߻��
	// �߽��� �Ǵ� �Ѿ��� ������ ��
	// �߽��� �Ǵ� �Ѿ��� �̵��Կ� ���� ������ �Ѿ˵� ���� �����̰Բ�
}
