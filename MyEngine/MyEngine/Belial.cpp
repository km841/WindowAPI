#include "pch.h"
#include "Belial.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "BelialCore.h"
#include "BelialHand.h"

Belial::Belial()
{
	mMonType = MONSTER_TYPE::BOSS_BELIAL;
	SetGravity(false);
	Texture* mTex = ResourceMgr::GetInstance().Load<Texture>(L"Belial_Body_Tex", L"Texture\\Belial_Body_Anim.bmp");

	SetBossName(L"������");
	SetBossComment(L"������ ������");

	std::wstring idleAnimName = L"Belial_Idle";
	SetIdleAnimName(idleAnimName);

	GetCollider()->SetSize(Vec2(100, 100));
	GetCollider()->SetOffset(Vec2(25, -50));

	GetAnimator()->RegisterAnimation(
		idleAnimName,
		mTex,
		Vec2(0, 0),
		Vec2(210, 297),
		Vec2(210, 0),
		0.1f,
		10
	);

	GetAnimator()->RegisterAnimation(
		L"Belial_Attack_Open",
		mTex,
		Vec2(0, 297),
		Vec2(210, 384),
		Vec2(210, 0),
		0.1f,
		10
	);

	GetAnimator()->RegisterAnimation(
		L"Belial_Attack_Close",
		mTex,
		Vec2(0, 681),
		Vec2(210, 384),
		Vec2(210, 0),
		0.1f,
		10
	);

	GetAnimator()->FindAnimation(idleAnimName)->SetTransMode(true, 3.f, TRANS_MODE::FADE_IN);

	GetAnimator()->SelectAnimation(idleAnimName, true);
	
	BelialCore* belialCore = new BelialCore;
	belialCore->SetOwner(this);
	belialCore->SetOffset(Vec2(25, 0));

	SetEffect(belialCore);
	// �Ĺ� Core�� Effect
	// Hand��? ����Ʈ�ε� �Ҹ��ڿ��� ���� ó��


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
	Vec2 leftHandPos = curPos;
	Vec2 rightHandPos = curPos;

	leftHandPos.x -= 400.f;
	rightHandPos.x += 400.f;

	mLeftHand->SetPos(leftHandPos);
	mRightHand->SetPos(rightHandPos);

	BossMonster::Initialize();

}

void Belial::Update()
{
	BossMonster::Update();

	if (nullptr != mLeftHand && nullptr != mRightHand)
	{
		mLeftHand->Update();
		mRightHand->Update();
	}

}

void Belial::Render()
{
	BossMonster::Render();

	if (nullptr != mLeftHand && nullptr != mRightHand)
	{
		mLeftHand->Render();
		mRightHand->Render();
	}
}

void Belial::Destroy()
{
	BossMonster::Destroy();
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
	return false;
}