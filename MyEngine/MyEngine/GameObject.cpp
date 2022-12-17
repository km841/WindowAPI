#include "pch.h"
#include "GameObject.h"
#include "Collider.h"
#include "Animator.h"
#include "RigidBody.h"
#include "KeyMgr.h"

GameObject::GameObject()
	: mScale(Vec2(1.f, 1.f))
	, mGround(true)
	, mGravity(false)
	, mPos{}
	, mSize{}
	, mComponents{}
	, mType()
	, mRelations()
	, mCollisionType(COLLISION_TYPE::NONE)
{
}

GameObject::~GameObject()
{
	Collider* collider = GetCollider();
	if (nullptr != collider)
	{
		delete collider;
		collider = nullptr;
	}

	Animator* animator = GetAnimator();
	if (nullptr != animator)
	{
		delete animator;
		animator = nullptr;
	}

	RigidBody* rigidBody = GetRigidBody();
	if (nullptr != rigidBody)
	{
		delete rigidBody;
		rigidBody = nullptr;
	}
}

GameObject::GameObject(const GameObject& _other)
	: mPos(_other.mPos)
	, mSize(_other.mSize)
	, mScale(_other.mScale)
	, mComponents{}
	, mType(_other.mType)
{
}

GameObject& GameObject::operator=(const GameObject& _other)
{
	mPos = _other.mPos;
	mSize = _other.mSize;
	mScale = _other.mScale;
	mComponents = {};
	mType = _other.mType;

	return *this;
}

void GameObject::Initialize()
{
}

void GameObject::Update()
{

	if (nullptr != GetAnimator())
		GetAnimator()->Update();

	if (nullptr != GetRigidBody())
		GetRigidBody()->Update();

	if (nullptr != GetCollider())
		GetCollider()->Update();
}

void GameObject::Render()
{

	if (IS_PRESSED(KEY::C))
	{
		if (nullptr != GetCollider())
			GetCollider()->Render();
	}

	if (nullptr != GetAnimator())
		GetAnimator()->Render();
}

void GameObject::Destroy()
{
}

void GameObject::SeverRelation(GameObject* _obj, RELATION_TYPE _relType)
{
	std::vector<Relation>::iterator iter = mRelations.begin();

	for (; iter != mRelations.end();)
	{
		if (_obj == iter->mOther)
		{
			iter = mRelations.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void GameObject::CreateComponent(Collider* _collider)
{
	assert(nullptr != _collider);
	mComponents.mCollider = _collider;
}

void GameObject::CreateComponent(Animator* _animator)
{
	assert(nullptr != _animator);
	mComponents.mAnimator = _animator;
}

void GameObject::CreateComponent(RigidBody* _rigidBody)
{
	assert(nullptr != _rigidBody);
	mComponents.mRigidBody = _rigidBody;
}
