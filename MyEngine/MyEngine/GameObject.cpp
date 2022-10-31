#include "pch.h"
#include "GameObject.h"
#include "Collider.h"
#include "Animator.h"

GameObject::GameObject()
	
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
}

void GameObject::Update()
{
	if (nullptr != GetCollider())
		GetCollider()->Update();

	if (nullptr != GetAnimator())
		GetAnimator()->Update();
}

void GameObject::Render()
{
	if (nullptr != GetCollider())
		GetCollider()->Render();

	if (nullptr != GetAnimator())
		GetAnimator()->Render();
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
