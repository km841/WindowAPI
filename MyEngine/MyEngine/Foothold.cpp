#include "pch.h"
#include "Foothold.h"
#include "Collider.h"
#include "Tile.h"
#include "Player.h"
#include "RigidBody.h"
#include "CameraMgr.h"

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
	//GetCollider()->SetOffset(Vec2(0.f, (TILE_SIZE / 2.f)));
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
			//player->GetRigidBody()->SetVelocity_Y(player->GetRigidBody()->GetVelocity_Y() * 0.95f);
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
	// �÷��̾ ������ �� ���� �־��ٸ� �ӵ��� ���߰� �о�ø�
	
	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		Vec2 pos = GetCollider()->GetPos();
		Vec2 size = GetCollider()->GetSize();

		Vec2 otherPos = _other->GetPos();
		Vec2 otherSize = _other->GetSize();

		float diff_y = (size.y / 2.f + otherSize.y / 2.f) - abs(pos.y - otherPos.y);
		Vec2 objectPos = _other->GetOwner()->GetPos();
		if (diff_y > 0.f)
		{
			if (diff_y < 1.f)
				return;

			objectPos.y -= 1;
			_other->GetOwner()->SetPos(objectPos);
		}
	}
}

void Foothold::OnCollisionEnter(Collider* _other)
{
	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		if (mPlayerAbobeMe)
			static_cast<Player*>(_other->GetOwner())->InGround();
	}
}

void Foothold::OnCollisionExit(Collider* _other)
{

}
