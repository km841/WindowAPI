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
	// 키 입력을 이용한 보스몬스터 스킬 조정
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
	// 보스 몬스터 소환
	// 카메라 시점 변환
	

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
