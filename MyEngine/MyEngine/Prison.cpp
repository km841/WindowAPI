#include "pch.h"
#include "Prison.h"
#include "Map.h"

Prison::Prison()
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
	AddMap(L"..\\Resource\\Map\\dungeon3_RTB.map");

	mCurMap = GetStartMap();
	// ��������� nullptr�� ã�Ƽ� ����
	
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
