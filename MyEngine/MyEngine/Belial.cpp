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
	Texture* tex = ResourceMgr::GetInstance().Load<Texture>(L"Belial_Body_Tex", L"Texture\\Monster\\Belial\\Belial_Body_Anim.bmp");
	Texture* hitTex = ResourceMgr::GetInstance().Load<Texture>(L"Belial_Body_HitTex", L"Texture\\Monster\\Belial\\Belial_Body_HitAnim.bmp");

	SetBossName(L"������");
	SetBossComment(L"������ ������");

	std::wstring idleAnimName = L"Belial_Idle";
	SetIdleAnimName(idleAnimName);

	GetCollider()->SetSize(Vec2(100, 100));
	GetCollider()->SetOffset(Vec2(25, -50));

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
		L"Belial_Attack_Open",
		tex,
		Vec2(0, 297),
		Vec2(210, 384),
		Vec2(210, 0),
		0.1f,
		10
	);

	GetAnimator()->RegisterAnimation(
		L"Belial_Attack_Close",
		tex,
		Vec2(0, 681),
		Vec2(210, 384),
		Vec2(210, 0),
		0.1f,
		10
	);

	GetAnimator()->FindAnimation(idleAnimName)->SetTransMode(true, 3.f, TRANS_MODE::FADE_IN);
	GetAnimator()->FindAnimation(idleAnimName)->SetHitAnimation(hitTex);

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
