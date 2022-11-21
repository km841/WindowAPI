#include "pch.h"
#include "Wall.h"
#include "Collider.h"
#include "Tile.h"

Wall::Wall()
{
	SetType(OBJECT_TYPE::WALL);
	CreateComponent(new Collider);
	GetCollider()->SetOwner(this);
	GetCollider()->SetSize(Vec2(TILE_SIZE, TILE_SIZE));
}

Wall::~Wall()
{
}

void Wall::Initialize()
{
	GetCollider()->SetPos(GetPos());
	GetCollider()->SetSize(GetSize());
	GetCollider()->SetOffset(Vec2(0.f, GetSize().y / 2.f));
}

void Wall::Update()
{
	if (nullptr != GetOwner())
		SetPos(GetOwner()->GetPos());

	GameObject::Update();
}

void Wall::Render()
{
	GameObject::Render();
}

void Wall::OnCollision(Collider* _other)
{
	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		// 내 충돌체와 상대 충돌체의 좌표와 크기를 비교해서 그만큼 뺌

		Vec2 pos = GetCollider()->GetPos();
		Vec2 size = GetCollider()->GetSize();

		Vec2 otherPos = _other->GetPos();
		Vec2 otherSize = _other->GetSize();

		float diff = (size.y / 2.f + otherSize.y / 2.f) - abs(pos.y - otherPos.y);

		Vec2 otherObjPos = _other->GetOwner()->GetPos();
		otherObjPos.y -= diff;
		_other->GetOwner()->SetPos(otherObjPos);

	}
}

void Wall::OnCollisionEnter(Collider* _other)
{
	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		// 내 충돌체와 상대 충돌체의 좌표와 크기를 비교해서 그만큼 뺌
		
		Vec2 pos = GetCollider()->GetPos();
		Vec2 size = GetCollider()->GetSize();

		Vec2 otherPos = _other->GetPos();
		Vec2 otherSize = _other->GetSize();

		float diff = (size.y / 2.f + otherSize.y / 2.f) - abs(pos.y - otherPos.y);
	
		Vec2 otherObjPos = _other->GetOwner()->GetPos();
		otherObjPos.y -= diff;
		_other->GetOwner()->SetPos(otherObjPos);
		
	}
}

void Wall::OnCollisionExit(Collider* _other)
{

}
