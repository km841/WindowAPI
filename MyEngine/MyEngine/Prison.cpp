#include "pch.h"
#include "Prison.h"
#include "Map.h"
#include "BelialBossMap.h"

Prison::Prison()
	:Stage(STAGE_TYPE::PRISON)
{
	mInitPlayerPos = Vec2(TILE_SIZE * 5, GROUND_STANDARD);
}

Prison::~Prison()
{
}

void Prison::Initialize()
{
	//AddMap(L"..\\Resource\\Map\\dungeon4.map");
	AddMap(L"..\\Resource\\Map\\start_map_TR.map");
	AddMap(L"..\\Resource\\Map\\dungeon2_LR.map");
	AddMap(L"..\\Resource\\Map\\dungeon4_RTB.map");
	AddMap(L"..\\Resource\\Map\\dungeon5_L.map");

	mCurMap = GetStartMap();
	// 재귀적으로 nullptr을 찾아서 조립

	SetBossSideMap(new Map(L"..\\Resource\\Map\\prison_side_map_r.map"));
	SetBossMap(new BelialBossMap(L"..\\Resource\\Map\\boss_map_LR.map"));
	
	ChainMaps(mCurMap);
	Stage::Initialize();
}

void Prison::Update()
{
	Stage::Update();
}

void Prison::Render()
{
}

void Prison::Destroy()
{
	Stage::Destroy();
}

void Prison::Enter()
{
	// 시작 맵으로 연결
	mCurMap->Enter();
}

void Prison::Exit()
{
	// 스테이지 정리
}
