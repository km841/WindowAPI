#include "pch.h"
#include "Bullet.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"

Bullet::Bullet()
{
	CreateComponent(new Collider);
	GetCollider()->SetOwner(this);

	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);
}

Bullet::~Bullet()
{
}

void Bullet::Initialize()
{
}

void Bullet::Update()
{
}

void Bullet::Render()
{
}

void Bullet::OnCollision(Collider* _other)
{
}

void Bullet::OnCollisionEnter(Collider* _other)
{
}

void Bullet::OnCollisionExit(Collider* _other)
{
}
