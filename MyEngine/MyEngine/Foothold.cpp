#include "pch.h"
#include "Foothold.h"
#include "Collider.h"
#include "Tile.h"
#include "Player.h"

Foothold::Foothold()
{
	SetType(OBJECT_TYPE::FOOTHOLD);
	SetSize(Vec2(TILE_SIZE, TILE_SIZE));
	CreateComponent(new Collider);
	GetCollider()->SetOwner(this);
	GetCollider()->SetSize(Vec2(TILE_SIZE, TILE_SIZE));
}

Foothold::~Foothold()
{
}

void Foothold::Initialize()
{
	GetCollider()->SetPos(GetPos());
	GetCollider()->SetSize(GetSize());
	//GetCollider()->SetOffset(Vec2(0.f, GetSize().y / 2.f));
}

void Foothold::Update()
{
	if (nullptr != GetOwner())
		SetPos(GetOwner()->GetPos());
	GameObject::Update();
}

void Foothold::Render()
{
	GameObject::Render();
}

void Foothold::OnCollision(Collider* _other)
{
	static_cast<Player*>(_other->GetOwner())->SetGroundType(TILE_TYPE::FOOTHOLD);
}

void Foothold::OnCollisionEnter(Collider* _other)
{

}

void Foothold::OnCollisionExit(Collider* _other)
{
	static_cast<Player*>(_other->GetOwner())->SetGroundType(TILE_TYPE::NONE);
}
