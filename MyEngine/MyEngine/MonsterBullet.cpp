#include "pch.h"
#include "MonsterBullet.h"

MonsterBullet::MonsterBullet()
{
	SetType(OBJECT_TYPE::MISSILE_FROM_MONSTER);
}

MonsterBullet::~MonsterBullet()
{
}

void MonsterBullet::Initialize()
{
}

void MonsterBullet::Update()
{
}

void MonsterBullet::Render()
{
}

void MonsterBullet::OnCollision(Collider* _other)
{
}

void MonsterBullet::OnCollisionEnter(Collider* _other)
{
}

void MonsterBullet::OnCollisionExit(Collider* _other)
{
}
