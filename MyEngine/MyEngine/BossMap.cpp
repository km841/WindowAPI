#include "pch.h"
#include "BossMap.h"

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
	// 카메라 포커싱
	// 보스 몬스터 소환

	Map::Enter();
}

void BossMap::Exit()
{
	Map::Exit();
}
