#include "pch.h"
#include "Wall.h"
#include "Collider.h"
#include "Tile.h"
#include "Player.h"
#include "CameraMgr.h"
#include "Monster.h"
#include "RigidBody.h"
#include "Gold.h"

Wall::Wall()
	:mPlayerBelowMe(false)
	,mPlayerAbobeMe(false)
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
}

void Wall::Update()
{
	GameObject::Update();

	Player* player = Player::GetPlayer();

	if (nullptr != player)
	{
		Vec2 playerColPos = player->GetCollider()->GetPos();
		Vec2 playerTilePos = CameraMgr::GetInstance().GetTileCoord(playerColPos);
		Vec2 myTilePos = CameraMgr::GetInstance().GetTileCoord(GetPos());

		Vec2 topTilePos = Vec2(myTilePos.x, myTilePos.y - TILE_SIZE);
		Vec2 leftTopTilePos = Vec2(myTilePos.x - TILE_SIZE, myTilePos.y - TILE_SIZE);
		Vec2 rightTopTilePos = Vec2(myTilePos.x + TILE_SIZE, myTilePos.y - TILE_SIZE);

		if (playerTilePos == topTilePos || 
			playerTilePos == myTilePos)
		{
			mPlayerAbobeMe = true;
		}
		else
			mPlayerAbobeMe = false;
	}
}

void Wall::Render()
{
	GameObject::Render();
}

void Wall::OnCollision(Collider* _other)
{
	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		// 나랑 같은 타일에 있는데 ~라면
		if (mPlayerAbobeMe)
		{
			if (false == Player::GetPlayer()->GetGround())
			{
				
				Player::GetPlayer()->InGround();
			}
		}

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

			if (2.f < diff_x)
			{
				otherObjPos.x += (diff_x + 1) * sign;
				otherPos.x += (diff_x + 1) * sign;
			}
		}

		else
		{
			int sign = 1;
			if (dirVec.y < 0.f)
			{
				sign = -sign;
			}

			if (2.f < diff_y)
			{
				otherObjPos.y += (diff_y)*sign;
				otherPos.y += (diff_y)*sign;
			}

		}

		_other->GetOwner()->SetPos(otherObjPos);
		_other->SetPos(otherPos);
	}

	if (OBJECT_TYPE::MONSTER == _other->GetOwner()->GetType())
	{
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

			if (5.f < diff_x)
			{
				otherObjPos.x += (diff_x + 1) * sign;
				otherPos.x += (diff_x + 1) * sign;
			}

		}

		else
		{
			int sign = 1;
			if (dirVec.y < 0.f)
			{
				sign = -sign;
			}

			if (5.f < diff_y)
			{
				otherObjPos.y += (diff_y)*sign;
				otherPos.y += (diff_y)*sign;
			}
		}

		_other->GetOwner()->SetPos(otherObjPos);
		_other->SetPos(otherPos);
	}

	if (OBJECT_TYPE::DROP_GOLD == _other->GetOwner()->GetType() || 
		OBJECT_TYPE::DROP_ITEM == _other->GetOwner()->GetType())
	{
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

			otherObjPos.x += (diff_x + 1) * sign;
			otherPos.x += (diff_x + 1) * sign;
		}

		else
		{
			int sign = 1;
			if (dirVec.y < 0.f)
			{
				sign = -sign;
			}

			otherObjPos.y += (diff_y) * sign;
			otherPos.y += (diff_y) * sign;
		}

		_other->GetOwner()->SetPos(otherObjPos);
		_other->SetPos(otherPos);
	}
}

void Wall::OnCollisionEnter(Collider* _other)
{
	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		if (mPlayerAbobeMe)
		{
			Player::GetPlayer()->SetDirectionVector(Vec2(0, 0));
			Player::GetPlayer()->SetCollisionType(COLLISION_TYPE::NORMAL);
			Player::GetPlayer()->GetRigidBody()->SetVelocity_Y_Zero();
		}
	}

	if (OBJECT_TYPE::MONSTER == _other->GetOwner()->GetType())
	{
		Monster* monster = static_cast<Monster*>(_other->GetOwner());
		monster->GetRigidBody()->SetVelocity_Y_Zero();
		static_cast<Monster*>(_other->GetOwner())->SetGround(true);

	}

	if (OBJECT_TYPE::DROP_GOLD == _other->GetOwner()->GetType())
	{
		_other->GetOwner()->GetRigidBody()->SetVelocity_Zero();
		_other->GetOwner()->SetGround(true);
	}

	if (OBJECT_TYPE::DROP_ITEM == _other->GetOwner()->GetType())
	{
		_other->GetOwner()->GetRigidBody()->SetVelocity_Zero();
		_other->GetOwner()->SetGround(true);
	}
}

void Wall::OnCollisionExit(Collider* _other)
{
}
