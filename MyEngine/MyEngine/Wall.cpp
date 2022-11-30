#include "pch.h"
#include "Wall.h"
#include "Collider.h"
#include "Tile.h"
#include "Player.h"
#include "CameraMgr.h"

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
}

void Wall::Update()
{
	GameObject::Update();

	Player* player = Player::GetPlayer();

	if (nullptr != player)
	{
		Vec2 playerTilePos = CameraMgr::GetInstance().GetTileCoord(player->GetCollider()->GetPos());
		Vec2 myTilePos = CameraMgr::GetInstance().GetTileCoord(GetPos());

		Vec2 topTilePos = Vec2(myTilePos.x, myTilePos.y - TILE_SIZE);
		if (playerTilePos == topTilePos)
		{
			mPlayerAbobeMe = true;
			//player->GetRigidBody()->SetVelocity_Y(player->GetRigidBody()->GetVelocity_Y() * 0.95f);
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
	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType() || 
		OBJECT_TYPE::MONSTER == _other->GetOwner()->GetType())
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
			otherPos.x += (diff_x + 1)* sign;
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
		
		//static_cast<Player*>(_other->GetOwner())->SetGroundType(TILE_TYPE::WALL);

	}
}

void Wall::OnCollisionEnter(Collider* _other)
{
	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		if (mPlayerAbobeMe)
			static_cast<Player*>(_other->GetOwner())->InGround();
	}
}

void Wall::OnCollisionExit(Collider* _other)
{
	//if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	//	Player::GetPlayer()->OutGround();
}
