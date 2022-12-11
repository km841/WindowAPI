#include "pch.h"
#include "Gold.h"
#include "Animator.h"
#include "Collider.h"
#include "RigidBody.h"
#include "EventRegisteror.h"

Gold::Gold()
	: mTexture(nullptr)
{
	SetType(OBJECT_TYPE::DROP_ITEM);

	CreateComponent(new Collider);
	GetCollider()->SetOwner(this);
	
	CreateComponent(new RigidBody);
	GetRigidBody()->SetOwner(this);

	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	GetCollider()->SetSize(Vec2(10, 10));
	GetCollider()->SetOffset(Vec2(0, -5));

	GetRigidBody()->SetMass(1.f);
}

Gold::~Gold()
{
}

void Gold::Initialize()
{
	GameObject::Initialize();
}

void Gold::Update()
{
	GameObject::Update();
}

void Gold::Render()
{
	GameObject::Render();
}

void Gold::Destroy()
{
	GameObject::Destroy();
}

void Gold::Drop(Gold* _gold, Vec2 _pos, int _money, float _angle)
{
	// 생성되면 튀어오르게 하는 방법?
	// 생성되자마자 RigidBody로 SetVelocity를 주면 됨 
	float radian = Math::DegreeToRadian(_angle);
	Vec2 rotVec = Math::RotateVector(Vec2(1, 0), radian);

	_gold->GetRigidBody()->SetVelocity(rotVec * 500.f);
	_gold->SetGround(false);
	_gold->SetMoney(_money);
	_gold->SetPos(_pos);

	EventRegisteror::GetInstance().CreateObject(_gold, _gold->GetType());
}

void Gold::OnCollision(Collider* _other)
{
}

void Gold::OnCollisionEnter(Collider* _other)
{
}

void Gold::OnCollisionExit(Collider* _other)
{
}
