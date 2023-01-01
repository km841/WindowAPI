#include "pch.h"
#include "Belial.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "BelialCore.h"
#include "BelialHand.h"
#include "BelialSword.h"
#include "EventRegisteror.h"
#include "TimeMgr.h"
#include "CameraMgr.h"

Belial::Belial()
	: mSwordSpawnMaxTime(0.3f)
	, mSwordSpawnCurTime(0.f)
	, mSwordMaxCount(SWORD_MAX_COUNT)
	, mSwordCurCount(0)
	, mHandType(BELIAL_HAND_TYPE::LEFT_HAND)
	
{
	mMonType = MONSTER_TYPE::BOSS_BELIAL;
	SetGravity(false);
	Texture* tex = ResourceMgr::GetInstance().Load<Texture>(L"Belial_Body_Tex", L"Texture\\Monster\\Belial\\Belial_Body_Anim.bmp");
	Texture* hitTex = ResourceMgr::GetInstance().Load<Texture>(L"Belial_Body_HitTex", L"Texture\\Monster\\Belial\\Belial_Body_HitAnim.bmp");

	SetBossName(L"������");
	SetBossComment(L"������ ������");

	std::wstring idleAnimName = L"Belial_Idle";
	SetIdleAnimName(idleAnimName);

	std::wstring skillAnimName = L"Belial_Attack";
	SetSkillAnimName(skillAnimName);

	SetSkill01AnimName(skillAnimName);


	GetCollider()->SetSize(Vec2(120, 120));
	GetCollider()->SetOffset(Vec2(25, -80));

	GetAnimator()->RegisterAnimation(
		idleAnimName,
		tex,
		Vec2(0, 0),
		Vec2(210, 297),
		Vec2(210, 0),
		0.1f,
		10
	);

	GetAnimator()->RegisterAnimation(
		skillAnimName,
		tex,
		Vec2(0, 297),
		Vec2(210, 384),
		Vec2(210, 0),
		0.1f,
		19
	);

	GetAnimator()->FindAnimation(idleAnimName)->SetTransMode(true, 3.f, TRANS_MODE::FADE_IN);
	GetAnimator()->FindAnimation(idleAnimName)->SetHitAnimation(hitTex);
	GetAnimator()->FindAnimation(skillAnimName)->SetHitAnimation(hitTex);
	GetAnimator()->FindAnimation(skillAnimName)->SetOffset(Vec2(0.f, 30.f));

	GetAnimator()->SelectAnimation(idleAnimName, true);

	// �ִϸ��̼ǿ��� ���� LT���� �����ͼ� LT���� ���� ����� �ٸ� ��������Ʈ ���Ϸ� �����.
	// �����°� ���ϵ�.
	// ���� ����� ���� �ش� �������� �ִϸ��̼��� ���� Ÿ�ֿ̹� �� �̹����� ���� �ָ� ��
	// �ִϸ��̼ǿ� ���� �����ؾ� �ǳ�?
	// �ǰ� �� �ִϸ��̼ǿ� ������ �ְ� �ִϸ��̼��� �ش� �����ӿ� �´� �ǰ� �ִϸ��̼��� ����ϸ� ��
	// �׸��� �ִϸ��̼� �ش� �������� ������ �Ǹ� �ǰ� �ִϸ��̼�(������) ����.

	// 1. �ǰ� �ִϸ��̼� ������ ������.
	// 2. �ǰ� �ִϸ��̼� ���� ���� TRUE�� ��쿡��
	// 3. Owner�� �ǰ� �޽����� ������ ��� �ش� LT���� �´� ���� �̹����� �������.
	// 4. �׷����� �ִϸ��̼ǿ� �ؽ��ĸ� �ϳ� �� �߰��ؾ� ��
	// 5. 1���������� �ϸ� �ʹ� ������ �����̶� �������� �Ȱ� Ƽ�� �ȳ� ���� ����
	// 6. �ð����� ���ؼ� n�ʵ��� ���� �ִϸ��̼��� ���������� ��
	// 7. die�� ��쿡��? �ִϸ��̼��� �ٲ�ϱ� ����� ����.
	
	BelialCore* belialCore = new BelialCore;
	belialCore->SetOwner(this);
	belialCore->SetOffset(Vec2(25, -15));

	SetEffect(belialCore);
	// �Ĺ� Core�� Effect
	// Hand��? ����Ʈ�ε� �Ҹ��ڿ��� ���� ó��

	SetAttFixFrame(9);

	mLeftHand = new BelialHand(BELIAL_HAND_TYPE::LEFT_HAND);
	mRightHand = new BelialHand(BELIAL_HAND_TYPE::RIGHT_HAND);
}

Belial::~Belial()
{
}

void Belial::Initialize()
{
	//BossHPHUD Ȱ��ȭ
	//BelialCore ��ȯ
	//Hand 2�� ��ȯ

	Vec2 curPos = GetPos();
	curPos += Vec2(25, -50);
	
	Vec2 leftHandPos = curPos;
	Vec2 rightHandPos = curPos;

	leftHandPos.x -= 400.f;
	leftHandPos.y += 150.f;

	rightHandPos.x += 400.f;
	rightHandPos.y -= 100.f;

	mLeftHand->SetPos(leftHandPos);
	mRightHand->SetPos(rightHandPos);

	BossMonster::Initialize();

}

void Belial::Update()
{
	

	if (IsAlive())
	{
		BossMonster::Update();

		if (nullptr != mLeftHand)
		{
			mLeftHand->Update();

		}

		if (nullptr != mRightHand)
		{
			mRightHand->Update();
		}
	}

	else
	{
		GetAnimator()->SelectAnimation(GetIdleAnimName(), false);
		GetAnimator()->GetCurAnimation()->Reset();
		GetAnimator()->GetCurAnimation()->SetFrameFix(true);
		GetAnimator()->GetCurAnimation()->DisableHitMode();

		mLeftHand->Dead();
		mRightHand->Dead();
	}



}

void Belial::Render()
{
	BossMonster::Render();

	if (nullptr != mLeftHand)
	{
		mLeftHand->Render();
	}

	if (nullptr != mRightHand)
	{
		mRightHand->Render();
	}
}

void Belial::Destroy()
{
	BossMonster::Destroy();

	if (nullptr != mLeftHand)
	{
		mLeftHand->Destroy();
		delete mLeftHand;
		mLeftHand = nullptr;
	}

	if (nullptr != mRightHand)
	{
		mRightHand->Destroy();
		delete mRightHand;
		mRightHand = nullptr;
	}

	for (int i = 0; i < mSwords.size(); ++i)
	{
		if (nullptr != mSwords[i])
		{
			delete mSwords[i];
			mSwords[i] = nullptr;
		}
	}


}

void Belial::OnCollision(Collider* _other)
{
}

void Belial::OnCollisionEnter(Collider* _other)
{
	BossMonster::OnCollisionEnter(_other);
}

void Belial::OnCollisionExit(Collider* _other)
{
}

bool Belial::Skill()
{
	// ��ų 1
	// ��ü ��ȯ�ؼ� �������� ������
	// effect���� �����ϱ�

	switch (GetCurSkill())
	{
	case BOSS_SKILL::SKILL_1:
	{
		return mEffect->Attack();
	}
		break;

	case BOSS_SKILL::SKILL_2:
		return BelialSwordSkill();
		break;

	case BOSS_SKILL::SKILL_3:
		return BelialLaserSkill();
		break;
	}


	return false;
}

bool Belial::BelialSwordSkill()
{
	Vec2 initPos = Vec2(500, 500);
	
	if (mSwordMaxCount <= mSwordCurCount)
	{
		mSwordSpawnCurTime = 0.f;
		mSwordCurCount = 0;
		return false;
	}

	else
	{
		if (mSwordSpawnMaxTime < mSwordSpawnCurTime)
		{
			mSwordSpawnCurTime = 0.f;

			initPos.x += mSwordCurCount * 150;
			BelialSword* sword = new BelialSword;
			sword->SetPos(initPos);

			mSwords.push_back(sword);
			EventRegisteror::GetInstance().CreateObject(sword, sword->GetType());

			++mSwordCurCount;
		}

		else
		{
			mSwordSpawnCurTime += DT;
		}
	}

	return true;
}

bool Belial::BelialLaserSkill()
{
	// left �����ϰ� right �����ϰ� left ����
	// bool���� ��ȯ�ؼ� ��� ���ٰ� ������ �ݴ��

	switch (mHandType)
	{
	case BELIAL_HAND_TYPE::LEFT_HAND:
	{
		if (!mLeftHand->Skill())
		{
			mHandType = BELIAL_HAND_TYPE::RIGHT_HAND;
			BelialHand::IncreaseLaserCount();

		}
	}
		break;

	case BELIAL_HAND_TYPE::RIGHT_HAND:
	{
		if (!mRightHand->Skill())
		{
			mHandType = BELIAL_HAND_TYPE::LEFT_HAND;
			BelialHand::IncreaseLaserCount();
		}
	}
		break;
	}

	if (BelialHand::IsLaserCountFinished())
	{
		BelialHand::ClearLaserCount();
		return false;
	}

	return true;
}

void Belial::Killed()
{
	CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::FADE_IN_FROM_WHITE, 3.0f);
	TimeMgr::GetInstance().SetDeltaTime(0.5f, 3.0f);

	SetObjState(OBJECT_STATE::DEAD_ANIM);
	// 1. ȭ��Ʈ Fade In
	// Dead����Ʈ�� ���� ����... �Լ�ȣ��->bool�� ����->update���� ������ ����Ʈ ����
	// 

	// DeadEffect���� �����ϰ� �ִϸ��̼��� ���� �Ŀ��� Core, Hand���� Destroy 
}

void Belial::Dead()
{

}
