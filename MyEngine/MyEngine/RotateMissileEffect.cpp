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
	, mBulletInterval(0.07f)
	, mCurTime(0.f)
	, mMaxBullet(20)
	, mReady(false)
	, mCurCoreBullet(nullptr)
{

}

RotateMissileEffect::~RotateMissileEffect()
{
}

void RotateMissileEffect::Initialize()
{
	MonsterMissileEffect::Initialize();
}

void RotateMissileEffect::Update()
{
	// Effect�� �߽����� ȸ���Ѵ�.

	MonsterMissileEffect::Update();
}

void RotateMissileEffect::Render()
{
	//mCoreBullet->Render();
}

void RotateMissileEffect::Destroy()
{
	if (nullptr != mCurCoreBullet)
	{
		mCurCoreBullet->SetAllDeadAnimChildBullet();
		delete mCurCoreBullet;
		mCurCoreBullet = nullptr;
	}
}

bool RotateMissileEffect::Attack()
{
	// Ư�� �����̸� �ΰ� n���� ������Ų��.
	// ������ ������ �׶����� �Ѿ��� �� �Ҹ��Ҷ�����
	// �Ҹ��� ������ ���� ��
	if (nullptr == mCurCoreBullet)
	{
		MonsterBullet* coreBullet = new MonsterBullet;
		coreBullet->SetBulletWayType(BULLET_WAY_TYPE::LINEAR);
		coreBullet->GetCollider()->SetEnable(false);
		mCurCoreBullet = coreBullet;
		mCoreBullets.push_back(coreBullet);

		Vec2 pos = GetPos();
		pos.y -= mRadius;
		mCurCoreBullet->SetPos(pos);
	}

	if (mMaxBullet > mCurCoreBullet->GetChildSize())
	{
		if (mBulletInterval < mCurTime)
		{
			mCurTime = 0.f;
			BatBullet* bullet = new BatBullet;
			bullet->GetCollider()->SetEnable(false);
			Vec2 coreBulletPos = mCurCoreBullet->GetPos();
			coreBulletPos.y -= mRadius;

			bullet->SetPos(coreBulletPos);
			bullet->SetRadius(mRadius);
			bullet->SetBulletWayType(BULLET_WAY_TYPE::ROTATE);
			bullet->SetStandardBullet(mCurCoreBullet);

			mCurCoreBullet->AddChildBullet(bullet);
			EventRegisteror::GetInstance().CreateObject(bullet, bullet->GetType());
		}

		else
		{
			mCurTime += DT;
		}
	}

	else
	{
		mCurCoreBullet->ChildColliderOn();

		Vec2 coreBulletPos = mCurCoreBullet->GetPos();
		Vec2 playerPos = Player::GetPlayer()->GetPos();

		mPlayerVec = playerPos - coreBulletPos;
		mPlayerVec.Norm();
		mCurCoreBullet->SetDir(mPlayerVec);

		EventRegisteror::GetInstance().CreateObject(mCurCoreBullet, mCurCoreBullet->GetType());
		mCurCoreBullet = nullptr;
		return false;
	}

	return true;

	// Bullet n���� �����
	// Bullet n���� missileEffect�� �߽����� ȸ��
	// n�� �Ŀ� �÷��̾� �������� �߻��
	// �߽��� �Ǵ� �Ѿ��� ������ ��
	// �߽��� �Ǵ� �Ѿ��� �̵��Կ� ���� ������ �Ѿ˵� ���� �����̰Բ�
}
