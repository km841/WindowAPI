#include "pch.h"
#include "Foothold.h"
#include "Collider.h"
#include "Tile.h"
#include "Player.h"
#include "RigidBody.h"

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
	//GetCollider()->SetOffset(Vec2(0.f, (TILE_SIZE / 2.f)));
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
	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		Vec2 pos = GetCollider()->GetPos();
		Vec2 size = GetCollider()->GetSize();

		Vec2 otherPos = _other->GetPos();
		Vec2 otherObjPos = _other->GetOwner()->GetPos();
		Vec2 otherSize = _other->GetSize();

		Vec2 dirVec = otherPos - pos;

		float diff_y = (size.y / 2.f + otherSize.y / 2.f) - abs(pos.y - otherPos.y);

		if (dirVec.y < 0.f && diff_y > 0.f )
		{
			if (diff_y < 1.f)
				return;

			otherObjPos.y -= 1;

			_other->GetOwner()->SetPos(otherObjPos);
			
		}
	}
	
}

void Foothold::OnCollisionEnter(Collider* _other)
{

}

void Foothold::OnCollisionExit(Collider* _other)
{
	//static_cast<Player*>(_other->GetOwner())->SetGroundType(TILE_TYPE::NONE);
}
