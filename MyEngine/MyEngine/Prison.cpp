#include "pch.h"
#include "Prison.h"
#include "Map.h"

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
	// ��������� nullptr�� ã�Ƽ� ����

	SetBossSideMap(new Map(L"..\\Resource\\Map\\prison_side_map_r.map"));

	
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
	// ���� ������ ����
	mCurMap->Enter();
}

void Prison::Exit()
{
	// �������� ����
}
