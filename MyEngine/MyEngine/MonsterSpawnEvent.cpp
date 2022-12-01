#include "pch.h"
#include "MonsterSpawnEvent.h"
#include "Collider.h"
#include "Animator.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Animation.h"
#include "MonsterFactory.h"
#include "EventRegisteror.h"

MonsterSpawnEvent::MonsterSpawnEvent(MONSTER_TYPE _monType)
	:mFlag(false)
	,mSpawnTiming(4)
{

	CreateComponent(new Collider);
	GetCollider()->SetOwner(this);

	GetCollider()->SetSize(Vec2(30.f, 30.f));
	GetCollider()->SetOffset(Vec2(0.f, -15.f));

	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	Texture* spawnAnimTex =
		ResourceMgr::GetInstance().Load<Texture>(L"MONSTER_SPAWN_TEX", L"Texture\\monster_spawn_animation.bmp");

	GetAnimator()->RegisterAnimation(
		L"MONSTER_SPAWN_ANIM",
		spawnAnimTex,
		Vec2(0.f, 0.f),
		Vec2(93, 93),
		Vec2(93, 0),
		0.06f,
		15
	);

	SetSize(Vec2(93, 93));
}

MonsterSpawnEvent::~MonsterSpawnEvent()
{
}

void MonsterSpawnEvent::Initialize()
{
}

void MonsterSpawnEvent::Update()
{
	EventObject::Update();
	Animation* curAnim = GetAnimator()->GetCurAnimation();
	if (mFlag)
	{
		int curFrame = curAnim->GetCurFrame();

		if (curFrame == mSpawnTiming)
		{
			Spawn();
			mFlag = false;
		}
	}

	else
	{
		if (nullptr != curAnim && curAnim->IsFinished())
		{
			EventRegisteror::GetInstance().DeleteObject(this);
		}
	}
}

void MonsterSpawnEvent::Render()
{
	EventObject::Render();
}

void MonsterSpawnEvent::Destroy()
{
}

void MonsterSpawnEvent::OnCollision(Collider* _other)
{
}

void MonsterSpawnEvent::OnCollisionEnter(Collider* _other)
{
	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		mFlag = true;
		GetAnimator()->SelectAnimation(L"MONSTER_SPAWN_ANIM", false);
		SetPos(mSpawnPos);
	}
}

void MonsterSpawnEvent::OnCollisionExit(Collider* _other)
{
}
