#include "pch.h"
#include "GiantSkullSpawnEvent.h"
#include "MonsterFactory.h"
#include "GiantSkullWarrior.h"
#include "EventRegisteror.h"

GiantSkullSpawnEvent::GiantSkullSpawnEvent()
	:MonsterSpawnEvent(MONSTER_TYPE::GROUND_MELEE)
{
}

GiantSkullSpawnEvent::~GiantSkullSpawnEvent()
{
}

void GiantSkullSpawnEvent::Initialize()
{
}

void GiantSkullSpawnEvent::Update()
{
	MonsterSpawnEvent::Update();
}

void GiantSkullSpawnEvent::Render()
{
	MonsterSpawnEvent::Render();
}

void GiantSkullSpawnEvent::Destroy()
{
}

void GiantSkullSpawnEvent::Spawn()
{
	GiantSkullWarrior* monster = static_cast<GiantSkullWarrior*>(MonsterFactory::CreateMonster<GiantSkullWarrior>(mMonsterType, mSpawnPos));
	monster->Initialize();

	EventRegisteror::GetInstance().CreateObject(monster, monster->GetType());
}

void GiantSkullSpawnEvent::OnCollision(Collider* _other)
{
}

void GiantSkullSpawnEvent::OnCollisionEnter(Collider* _other)
{
	MonsterSpawnEvent::OnCollisionEnter(_other);
}

void GiantSkullSpawnEvent::OnCollisionExit(Collider* _other)
{
}
