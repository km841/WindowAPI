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

Texture* Monster::mHPBaseTex = nullptr;
Texture* Monster::mHPTex     = nullptr;

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

	if (nullptr == mHPBaseTex)
	{
		mHPBaseTex = ResourceMgr::GetInstance().Load<Texture>(L"MonsterHPBaseTex", L"Texture\\MONSTER_HP_BASE.bmp");
	}

	if (nullptr == mHPTex)
	{
		mHPTex = ResourceMgr::GetInstance().Load<Texture>(L"MonsterHPTex", L"Texture\\MONSTER_HP.bmp");
	}

	
}

Monster::~Monster()
{
	if (nullptr != mAI)
	{
		delete mAI;
		mAI = nullptr;
	}

	// 삭제될 때 씬에서도 지워줘야 함
	
	
	//if (nullptr != mEffect)
	//{
	//	delete mEffect;
	//	mEffect = nullptr;
	//}
}

void Monster::Initialize()
{
	mInfo.mCurHP = mInfo.mMaxHP;

	Effect* effect = GetEffect();
	if (nullptr != effect)
	{
		effect->SetPos(GetPos());
		effect->Initialize();
		EventRegisteror::GetInstance().CreateObject(effect, effect->GetType());
	}
	
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

	// 몬스터의 체력이 100%가 아니라면 hpbar 위치를 받아서 출력


	GameObject::Render();
	float ratio = mInfo.mCurHP / mInfo.mMaxHP;
	if (1 > ratio)
	{
		Vec2 pos = GetPos();
		pos += mHPBarOffset;
		pos = RENDER_POS(pos);
		Vec2 hpBaseSize = mHPBaseTex->GetSize();
		Vec2 hpSize = mHPTex->GetSize();

		BitBlt(
			BACK_BUF_DC,
			(int)(pos.x - hpBaseSize.x / 2),
			(int)(pos.y - hpBaseSize.y / 2),
			(int)hpBaseSize.x,
			(int)hpBaseSize.y,
			mHPBaseTex->GetDC(),
			0, 0,
			SRCCOPY
		);

		BitBlt(
			BACK_BUF_DC,
			(int)(pos.x - hpSize.x / 2),
			(int)(pos.y - hpSize.y / 2),
			(int)(hpSize.x * ratio),
			(int)hpSize.y,
			mHPTex->GetDC(),
			0, 0,
			SRCCOPY
		);
	}
}

void Monster::Destroy()
{
	if (nullptr != mEffect)
		EventRegisteror::GetInstance().DeleteObject(mEffect);

	// 씬의 Exit에서 삭제하도록 함
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

}
