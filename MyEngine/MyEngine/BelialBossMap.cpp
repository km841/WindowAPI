#include "pch.h"
#include "BelialBossMap.h"

BelialBossMap::BelialBossMap(const std::wstring& _path)
	:BossMap(_path)
{
}

BelialBossMap::~BelialBossMap()
{
}

void BelialBossMap::Initialize()
{
	BossMap::Initialize();
}

void BelialBossMap::Update()
{
	BossMap::Update();
	// Ű �Է��� �̿��� �������� ��ų ����
}

void BelialBossMap::Render()
{
}

void BelialBossMap::Destroy()
{
	BossMap::Destroy();
}

void BelialBossMap::Enter()
{
	// ���� ���� ��ȯ
	// ī�޶� ���� ��ȯ

}

void BelialBossMap::Exit()
{
}
