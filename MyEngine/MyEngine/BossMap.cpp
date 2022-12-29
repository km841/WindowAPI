#include "pch.h"
#include "BossMap.h"
#include "BossHPHUD.h"
#include "EventRegisteror.h"
#include "UIMgr.h"

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

	if (nullptr != mBossMonster)
	{
		GET_BOSSHP_HUD->SetBossMonster(mBossMonster);
		EventRegisteror::GetInstance().EnableHUD(HUD_TYPE::BOSS_HP);
	}

}

void BossMap::Exit()
{
	Map::Exit();
}
