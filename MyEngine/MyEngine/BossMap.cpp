#include "pch.h"
#include "BossMap.h"
#include "BossHPHUD.h"
#include "EventRegisteror.h"
#include "UIMgr.h"
#include "BossMonster.h"
#include "TimeMgr.h"

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
	// ���� Ű�Է����� ���� ��ų
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
	// ī�޶� ��Ŀ��
	// ���� ���� ��ȯ
	Map::Enter();

}

void BossMap::Exit()
{
	Map::Exit();
}