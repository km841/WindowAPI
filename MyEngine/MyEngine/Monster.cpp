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

Monster::Monster()
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
}

void Monster::Initialize()
{

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
