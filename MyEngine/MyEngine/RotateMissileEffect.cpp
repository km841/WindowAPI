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
{
	mCoreBullet = new MonsterBullet;
	mCoreBullet->SetBulletWayType(BULLET_WAY_TYPE::LINEAR);
	mCoreBullet->GetCollider()->SetEnable(false);
	EventRegisteror::GetInstance().CreateObject(mCoreBullet, mCoreBullet->GetType());
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

	// �Ѿ��� ���� �����ƴٸ�
	if (mReady)
	{
		if (mCoreBullet->AllDeadChildBullet())
		{
			mReady = false;
			Vec2 pos = GetPos();
			pos.y -= 80;
			mCoreBullet->SetPos(pos);
			mCoreBullet->SetDir(ZERO_VECTOR);
			mCoreBullet->ClearChildBullet();
		}
	}

	else
	{
		Vec2 pos = GetPos();
		pos.y -= 80;
		mCoreBullet->SetPos(pos);
	}
}

void RotateMissileEffect::Render()
{
	//mCoreBullet->Render();
}

void RotateMissileEffect::Destroy()
{
	mCoreBullet->SetAllDeadAnimChildBullet();
}

bool RotateMissileEffect::Attack()
{
	// Ư�� �����̸� �ΰ� n���� ������Ų��.
	// ������ ������ �׶����� �Ѿ��� �� �Ҹ��Ҷ�����
	// �Ҹ��� ������ ���� ��

	if (mMaxBullet > mCoreBullet->GetChildSize())
	{
		if (mBulletInterval < mCurTime)
		{
			mCurTime = 0.f;
			BatBullet* bullet = new BatBullet;
			bullet->GetCollider()->SetEnable(false);
			Vec2 coreBulletPos = mCoreBullet->GetPos();
			coreBulletPos.y -= mRadius;
			bullet->SetPos(coreBulletPos);
			bullet->SetRadius(mRadius);
			bullet->SetBulletWayType(BULLET_WAY_TYPE::ROTATE);
			bullet->SetStandardBullet(mCoreBullet);

			mCoreBullet->AddChildBullet(bullet);
			
			EventRegisteror::GetInstance().CreateObject(bullet, bullet->GetType());
		}

		else
		{
			mCurTime += DT;
		}
	}

	else
	{
		mCoreBullet->ChildColliderOn();

		mPlayerVec = ZERO_VECTOR;

		Vec2 coreBulletPos = mCoreBullet->GetPos();
		Vec2 playerPos = Player::GetPlayer()->GetPos();

		mPlayerVec = playerPos - coreBulletPos;
		mPlayerVec.Norm();
		mCoreBullet->SetDir(mPlayerVec);

		mReady = true;
		return false;
	}


	return true;

	// Bullet n���� �����
	// Bullet n���� missileEffect�� �߽����� ȸ��
	// n�� �Ŀ� �÷��̾� �������� �߻��
	// �߽��� �Ǵ� �Ѿ��� ������ ��
	// �߽��� �Ǵ� �Ѿ��� �̵��Կ� ���� ������ �Ѿ˵� ���� �����̰Բ�
}
