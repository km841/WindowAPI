#include "pch.h"
#include "RedGiantBatSpawnEvent.h"
#include "MonsterFactory.h"
#include "RedGiantBat.h"
#include "EventRegisteror.h"

RedGiantBatSpawnEvent::RedGiantBatSpawnEvent()
	:MonsterSpawnEvent(MONSTER_TYPE::FLY_RANGE)
{
}

RedGiantBatSpawnEvent::~RedGiantBatSpawnEvent()
{
}

void RedGiantBatSpawnEvent::Initialize()
{
}

void RedGiantBatSpawnEvent::Update()
{
	MonsterSpawnEvent::Update();
}

void RedGiantBatSpawnEvent::Render()
{
	MonsterSpawnEvent::Render();
}

void RedGiantBatSpawnEvent::Destroy()
{
}

void RedGiantBatSpawnEvent::Spawn()
{
	RedGiantBat* monster = 
		static_cast<RedGiantBat*>(MonsterFactory::CreateMonster<RedGiantBat>(mMonsterType, mSpawnPos));
	monster->Initialize();

	EventRegisteror::GetInstance().CreateObject(monster, monster->GetType());
}

void RedGiantBatSpawnEvent::OnCollision(Collider* _other)
{
}

void RedGiantBatSpawnEvent::OnCollisionEnter(Collider* _other)
{
	MonsterSpawnEvent::OnCollisionEnter(_other);
}

void RedGiantBatSpawnEvent::OnCollisionExit(Collider* _other)
{
}
