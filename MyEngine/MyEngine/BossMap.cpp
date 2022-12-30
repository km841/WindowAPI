#include "pch.h"
#include "BossMap.h"
#include "BossHPHUD.h"
#include "EventRegisteror.h"
#include "UIMgr.h"
#include "BossMonster.h"
#include "TimeMgr.h"
#include "MinimapHUD.h"

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

	if (nullptr != mBossMonster)
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
}

void BossMap::Exit()
{
	Map::Exit();
	EventRegisteror::GetInstance().EnableHUD(HUD_TYPE::MINIMAP);
}
