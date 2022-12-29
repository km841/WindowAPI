#include "pch.h"
#include "BelialBossMap.h"
#include "MonsterFactory.h"
#include "Belial.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "BossHPHUD.h"
#include "Player.h"
#include "TimeMgr.h"
#include "CameraMgr.h"
#include "EventRegisteror.h"
#include "MonsterEffect.h"

BelialBossMap::BelialBossMap(const std::wstring& _path)
	:BossMap(_path)
	, mBossActiveArea(500.f)
	, mMaxDuration(5.0f)
	, mCurDuration(0.f)
	, mBossActive(false)
	, mBossAppearing(false)
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
	
	if (false == mBossActive)
	{
		if (true == mBossAppearing)
		{
			if (mMaxDuration < mCurDuration)
			{
				// HUD 끄기
				Player::GetPlayer()->SetStop(false);
				mBossActive = true;
				CameraMgr::GetInstance().SetTrackingObject(Player::GetPlayer());
			}

			else
			{
				mCurDuration += DT;			
			}
		}

		else
		{
			Player* player = Player::GetPlayer();

			if (nullptr != player)
			{
				Vec2 playerPos = player->GetPos();

				if (playerPos.x > mBossActiveArea)
				{
					mBossAppearing = true;
					player->SetStop(true);

					EventRegisteror::GetInstance().EnableHUD(HUD_TYPE::BOSS_APPEAR);

					mBossMonster = static_cast<Belial*>(
						MonsterFactory::CreateMonster<Belial>(MONSTER_TYPE::BOSS_BELIAL, Vec2(770, 900)));

					mBossMonster->Initialize();
					SceneMgr::GetInstance().GetCurScene()->AddGameObject(mBossMonster, mBossMonster->GetType());

					Vec2 bossMonsterPos = mBossMonster->GetPos();
					bossMonsterPos.y -= 65.f;

					CameraMgr::GetInstance().SetTrackingObject(nullptr);
					CameraMgr::GetInstance().SetLookPos(bossMonsterPos);
				}
			}
		}
	}



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
	




	BossMap::Enter();
}

void BelialBossMap::Exit()
{
	BossMap::Exit();
}
