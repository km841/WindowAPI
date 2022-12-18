#include "pch.h"
#include "Item.h"
#include "Collider.h"
#include "RigidBody.h"
#include "EventRegisteror.h"

Item::Item()
	: mItemType(ITEM_TYPE::END)
	, mItemInfo{}
	, mTexture(nullptr)
	, mIconTexture(nullptr)
	, mEquipedTex(nullptr)
{
	CreateComponent(new Collider);
	GetCollider()->SetOwner(this);

	CreateComponent(new RigidBody);
	GetRigidBody()->SetOwner(this);

	GetRigidBody()->SetMass(1.f);

	GetCollider()->SetSize(Vec2(10.f, 10.f));
	GetCollider()->SetOffset(Vec2(0.f, 10.f));
}

Item::~Item()
{

}

void Item::Initialize()
{
}

void Item::Update()
{
}

void Item::Render()
{
}

void Item::Destroy()
{
}

void Item::Drop(Vec2 _pos)
{
	mHasFallen = true;
	SetGround(false);
	GetRigidBody()->SetVelocity_Y(-500.f);
	SetPos(_pos);
	EventRegisteror::GetInstance().CreateObject(this, GetType());
}
