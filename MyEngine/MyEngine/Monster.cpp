#include "pch.h"
#include "Monster.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "EventRegisteror.h"
#include "CameraMgr.h"
#include "RigidBody.h"
#include "AI.h"
#include "MonsterEffect.h"

Monster::Monster()
	: mDead(false)
	, mAI(nullptr)
	, mInfo()
	, mDir(DIR::END)
	, mPrevDir(DIR::END)
{
	SetType(OBJECT_TYPE::MONSTER);

	CreateComponent(new Collider);
	GetCollider()->SetOwner(this);

	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	CreateComponent(new RigidBody);
	GetRigidBody()->SetOwner(this);
}

Monster::~Monster()
{
	if (nullptr != mAI)
	{
		delete mAI;
		mAI = nullptr;
	}

	// ������ �� �������� ������� ��
	
	
	//if (nullptr != mEffect)
	//{
	//	delete mEffect;
	//	mEffect = nullptr;
	//}
}

void Monster::Initialize()
{
	EventRegisteror::GetInstance().CreateObject(GetEffect(), GetEffect()->GetType());
}

void Monster::Update()
{
	if (nullptr != mAI)
		mAI->Update();

	GameObject::Update();
}

void Monster::Render()
{
	if (nullptr != mAI)
		mAI->Render();

	GameObject::Render();
}

void Monster::Destroy()
{
	EventRegisteror::GetInstance().DeleteObject(mEffect);
	// ���� Exit���� �����ϵ��� ��
	//EventRegisteror::GetInstance().DeleteObject(mEffect);
	//mEffect = nullptr;
}

void Monster::OnCollision(Collider* _other)
{
}

void Monster::OnCollisionEnter(Collider* _other)
{
}

void Monster::OnCollisionExit(Collider* _other)
{
	if (0 == GetCollider()->GetColCnt())
		SetGround(false);
}
