#include "pch.h"
#include "GiantBatSpawnEvent.h"
#include "MonsterFactory.h"
#include "GiantBat.h"
#include "EventRegisteror.h"

GiantBatSpawnEvent::GiantBatSpawnEvent()
	:MonsterSpawnEvent(MONSTER_TYPE::FLY_RANGE)
{
}

GiantBatSpawnEvent::~GiantBatSpawnEvent()
{
}

void GiantBatSpawnEvent::Initialize()
{
}

void GiantBatSpawnEvent::Update()
{
	MonsterSpawnEvent::Update();
}

void GiantBatSpawnEvent::Render()
{
	MonsterSpawnEvent::Render();
}

void GiantBatSpawnEvent::Destroy()
{
}

void GiantBatSpawnEvent::Spawn()
{
	GiantBat* monster =
		static_cast<GiantBat*>(MonsterFactory::CreateMonster<GiantBat>(mMonsterType, mSpawnPos));
	monster->Initialize();

	EventRegisteror::GetInstance().CreateObject(monster, monster->GetType());
}

void GiantBatSpawnEvent::OnCollision(Collider* _other)
{
}

void GiantBatSpawnEvent::OnCollisionEnter(Collider* _other)
{
	MonsterSpawnEvent::OnCollisionEnter(_other);
}

void GiantBatSpawnEvent::OnCollisionExit(Collider* _other)
{
}
