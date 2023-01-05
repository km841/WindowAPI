#include "pch.h"
#include "BossMap.h"
#include "BossHPHUD.h"
#include "EventRegisteror.h"
#include "UIMgr.h"
#include "BossMonster.h"
#include "TimeMgr.h"
#include "MinimapHUD.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "Stage.h"
#include "CollisionMgr.h"

BossMap::BossMap(const std::wstring& _path)
	:Map(_path)
{
}

BossMap::~BossMap()
{
}

void BossMap::Initialize()
{
	Map::Initialize();
}

void BossMap::Update()
{
	Map::Update();

	if (nullptr != mBossMonster && mBossMonster->IsAlive())
	{
		GET_BOSSHP_HUD->SetBossMonster(mBossMonster);
		if (false == GET_BOSSHP_HUD->GetState())
		{
			EventRegisteror::GetInstance().EnableHUD(HUD_TYPE::BOSS_HP);
		}
	}
	// 각종 키입력으로 보스 스킬
}

void BossMap::Render()
{
	
}

void BossMap::Destroy()
{
	Map::Destroy();
}

void BossMap::Enter()
{
	Map::Enter();
	EventRegisteror::GetInstance().DisableHUD(HUD_TYPE::MINIMAP);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::DUNGEON_OBJECT, OBJECT_TYPE::WALL);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::DUNGEON_OBJECT, OBJECT_TYPE::FOOTHOLD);
}

void BossMap::Exit()
{
	Map::Exit();
	EventRegisteror::GetInstance().EnableHUD(HUD_TYPE::MINIMAP);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::DUNGEON_OBJECT, OBJECT_TYPE::WALL);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::DUNGEON_OBJECT, OBJECT_TYPE::FOOTHOLD);
	
	GetOwnerStage()->SetClear(true);
	//SceneMgr::GetInstance().GetCurScene()->DeleteObjGroup(OBJECT_TYPE::MONSTER_EFFECT);

}
