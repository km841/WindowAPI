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
