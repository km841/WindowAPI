#include "pch.h"
#include "Foothold.h"
#include "Collider.h"
#include "Tile.h"
#include "Player.h"

Foothold::Foothold()
{
	SetType(OBJECT_TYPE::FOOTHOLD);
	SetSize(Vec2(TILE_SIZE, 1));
	CreateComponent(new Collider);
	GetCollider()->SetOwner(this);
	GetCollider()->SetSize(Vec2(TILE_SIZE, 1));
}

Foothold::~Foothold()
{
}

void Foothold::Initialize()
{
	GetCollider()->SetPos(GetPos());
	GetCollider()->SetSize(GetSize());
	GetCollider()->SetOffset(Vec2(0.f, GetSize().y / 2.f));
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
	//static_cast<Player*>(_other->GetOwner())->SetGroundType(TILE_TYPE::FOOTHOLD);

	// �÷��̾ �� ���ʿ� �ִٸ� Groundó��

	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		// �÷��̾ ���� ���ø���.

		//���ϰ� ������ �浹

		Player* player = static_cast<Player*>(_other->GetOwner());
		Vec2 playerPos = player->GetPos();
		Vec2 playerSize = player->GetSize();

		//y = ax + b


		// ���� �����ϸ� �� ���� �������� �ذ� �ȴ�

	}
}

void Foothold::OnCollisionEnter(Collider* _other)
{

}

void Foothold::OnCollisionExit(Collider* _other)
{
	//static_cast<Player*>(_other->GetOwner())->SetGroundType(TILE_TYPE::NONE);
}
