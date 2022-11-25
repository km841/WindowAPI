#include "pch.h"
#include "Wall.h"
#include "Collider.h"
#include "Tile.h"
#include "Player.h"

Wall::Wall()
{
	SetType(OBJECT_TYPE::WALL);
	SetSize(Vec2(TILE_SIZE, TILE_SIZE));
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
		Vec2 pos = GetCollider()->GetPos();
		Vec2 size = GetCollider()->GetSize();

		Vec2 otherPos = _other->GetPos();
		Vec2 otherSize = _other->GetSize();

		Vec2 dirVec = otherPos - pos;

		float diff_x = (size.x / 2.f + otherSize.x / 2.f) - abs(pos.x - otherPos.x);
		float diff_y = (size.y / 2.f + otherSize.y / 2.f) - abs(pos.y - otherPos.y);

		Vec2 otherObjPos = _other->GetOwner()->GetPos();
		int sign = 1;
		if (diff_x < diff_y)
		{
			
			if (dirVec.x < 0.f)
			{
				sign = -sign;
			}

			otherObjPos.x += diff_x * sign;
			otherPos.x += diff_x * sign;
		}

		else
		{
			if (dirVec.y < 0.f)
			{
				sign = -sign;
			}

			otherObjPos.y += diff_y * sign;
			otherPos.y += diff_y * sign;
		}

		_other->GetOwner()->SetPos(otherObjPos);
		_other->SetPos(otherPos);



		//static_cast<Player*>(_other->GetOwner())->SetGroundType(TILE_TYPE::WALL);

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

		Vec2 dirVec = otherPos - pos;

		float diff_x = (size.x / 2.f + otherSize.x / 2.f) - abs(pos.x - otherPos.x);
		float diff_y = (size.y / 2.f + otherSize.y / 2.f) - abs(pos.y - otherPos.y);

		Vec2 otherObjPos = _other->GetOwner()->GetPos();
		if (diff_x < diff_y)
		{
			int sign = 1;
			if (dirVec.x < 0.f)
			{
				sign = -sign;
			}

			otherObjPos.x += diff_x * sign;
			otherPos.x += diff_x * sign;
		}

		else
		{
			int sign = 1;
			if (dirVec.y < 0.f)
			{
				sign = -sign;
			}

			otherObjPos.y += diff_y * sign;
			otherPos.y += diff_y * sign;
		}

		_other->GetOwner()->SetPos(otherObjPos);
		_other->SetPos(otherPos);

		// 벽과 내 위치에 따라서 침범한 두 곳 중 어느 곳으로 밀어낼 지 결정

	}
}

void Wall::OnCollisionExit(Collider* _other)
{
	//static_cast<Player*>(_other->GetOwner())->SetGroundType(TILE_TYPE::NONE);
}
