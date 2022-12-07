#include "pch.h"
#include "PlayerBullet.h"

PlayerBullet::PlayerBullet()
{
	SetType(OBJECT_TYPE::MISSILE_FROM_PLAYER);
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Initialize()
{
}

void PlayerBullet::Update()
{
}

void PlayerBullet::Render()
{
}

void PlayerBullet::OnCollision(Collider* _other)
{
}

void PlayerBullet::OnCollisionEnter(Collider* _other)
{
}

void PlayerBullet::OnCollisionExit(Collider* _other)
{
}
