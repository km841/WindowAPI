#include "pch.h"
#include "BelialBossMap.h"
#include "MonsterFactory.h"
#include "Belial.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "BossHPHUD.h"

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
	

	mBossMonster = static_cast<Belial*>(
		MonsterFactory::CreateMonster<Belial>(MONSTER_TYPE::BOSS_BELIAL, Vec2(770, 900)));

	mBossMonster->Initialize();
	SceneMgr::GetInstance().GetCurScene()->AddGameObject(mBossMonster, mBossMonster->GetType());


	BossMap::Enter();
}

void BelialBossMap::Exit()
{
	BossMap::Exit();
}
