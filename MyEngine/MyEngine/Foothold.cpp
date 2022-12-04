#include "pch.h"
#include "Foothold.h"
#include "Collider.h"
#include "Tile.h"
#include "Player.h"
#include "RigidBody.h"
#include "CameraMgr.h"
#include "Monster.h"
#include "LineCollider.h"

Foothold::Foothold()
{
	SetType(OBJECT_TYPE::FOOTHOLD);
	SetSize(Vec2(TILE_SIZE, TILE_SIZE));
	CreateComponent(new LineCollider);
	GetCollider()->SetOwner(this);
	GetCollider()->SetSize(Vec2(TILE_SIZE, TILE_SIZE));
}

Foothold::~Foothold()
{
}

void Foothold::Initialize()
{
	GetCollider()->SetPos(GetPos());
}

void Foothold::Update()
{

	GameObject::Update();
	
	Player* player =Player::GetPlayer();

	if (nullptr != player)
	{
		Vec2 playerTilePos = CameraMgr::GetInstance().GetTileCoord(player->GetCollider()->GetPos());
		Vec2 myTilePos = CameraMgr::GetInstance().GetTileCoord(GetPos());

		Vec2 topTilePos= Vec2(myTilePos.x, myTilePos.y - TILE_SIZE);
		if (playerTilePos == topTilePos)
		{
			mPlayerAbobeMe = true;
		}
		else
			mPlayerAbobeMe = false;
	}

}

void Foothold::Render()
{
	GameObject::Render();
}

void Foothold::OnCollision(Collider* _other)
{
	// 플레이어가 이전에 내 위에 있었다면 속도를 낮추고 밀어올림
	
	//if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	//{
	//	Vec2 pos = GetCollider()->GetPos();
	//	Vec2 size = GetCollider()->GetSize();

	//	Vec2 otherPos = _other->GetPos();
	//	Vec2 otherSize = _other->GetSize();

	//	float diff_y = (size.y / 2.f + otherSize.y / 2.f) - abs(pos.y - otherPos.y);
	//	Vec2 objectPos = _other->GetOwner()->GetPos();
	//	if (diff_y > 0.f)
	//	{
	//		if (diff_y < 3.f)
	//			return;

	//		objectPos.y -= 1;
	//		_other->GetOwner()->SetPos(objectPos);
	//	}
	//}

	//if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	//{
	//	if (false == _other->GetOwner()->GetGround())
	//		static_cast<Player*>(_other->GetOwner())->InGround();
	//}
}

void Foothold::OnCollisionEnter(Collider* _other)
{
	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{

		Player* player = Player::GetPlayer();
		player->InGround();
		player->SetCollisionType(COLLISION_TYPE::LINE);
		
		Vec2 otherPos = _other->GetPos();
		LineCollider* collider = static_cast<LineCollider*>(GetCollider());
		Vec2 dirVec = collider->GetRightDotPos() - collider->GetLeftDotPos();
		dirVec.Norm();
		player->SetDirectionVector(dirVec);
			
		
	}

	if (OBJECT_TYPE::MONSTER == _other->GetOwner()->GetType())
	{
		static_cast<Monster*>(_other->GetOwner())->SetGround(true);
	}
}

void Foothold::OnCollisionExit(Collider* _other)
{
	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		//Player::GetPlayer()->SetDirectionVector(ZERO_VECTOR);
		//Player::GetPlayer()->SetCollisionType(COLLISION_TYPE::NONE);
	}
}
