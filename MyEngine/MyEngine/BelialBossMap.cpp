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
#include "UIMgr.h"
#include "BossAppearHUD.h"
#include "CollisionMgr.h"
#include "BoomEffect.h"

BelialBossMap::BelialBossMap(const std::wstring& _path)
	:BossMap(_path)
	, mBossActiveArea(500.f)
	, mMaxDuration(5.0f)
	, mCurDuration(0.f)
	, mBossActive(false)
	, mBossAppearing(false)
	, mDeadStayMaxTime(3.f)
	, mDeadStayCurTime(0.f)
	, mDeadStayFlag(false)
	, mBoomMaxCount(60)
	, mBoomCurCount(0)
	, mBoomMaxTime(0.1f)
	, mBoomCurTime(0.f)
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
	if (mBossActive)
		BossMap::Update();

	// 키 입력을 이용한 보스몬스터 스킬 조정

	if (nullptr != mBossMonster)
	{
		if (mBossMonster->IsDeadAnim())
		{
			// n초 대기

			if (mDeadStayMaxTime < mDeadStayCurTime)
			{
				// 이펙트 실행
				// 보스 위치로 가서 일정 범위내에 폭발이펙트
				mDeadStayFlag = true;
				CameraMgr::GetInstance().SetTrackingObject(nullptr);
				CameraMgr::GetInstance().SetLookPos(mBossMonster->GetPos());
				
			}

			else
			{
				mDeadStayCurTime += DT;
			}
		}


		if (false == mBossMonster->IsDead() &&
			true == mDeadStayFlag)
		{
			if (mBoomMaxCount < mBoomCurCount)
			{
				// 상자 생성
				//CameraMgr::GetInstance().SetLookPos(Player::GetPlayer()->GetPos());
				CameraMgr::GetInstance().SetTrackingObject(Player::GetPlayer());
				mBossMonster->SetObjState(OBJECT_STATE::DEAD);
				mBossMonster->GetEffect()->SetObjState(OBJECT_STATE::DEAD);
				EventRegisteror::GetInstance().DisableHUD(HUD_TYPE::BOSS_HP);
			}

			else
			{
				if (mBoomMaxTime < mBoomCurTime)
				{
					++mBoomCurCount;
					mBoomCurTime = 0.f;
					Vec2 bossPos = mBossMonster->GetPos();
					Vec2 ltPoint = bossPos - 200.f;
					ltPoint.y -= 80.f;

					float rand_x = (float)(rand() % 400);
					float rand_y = (float)(rand() % 400);

					ltPoint.x += rand_x;
					ltPoint.y += rand_y;

					BoomEffect* effect = new BoomEffect;
					effect->SetPos(ltPoint);


					mEffects.push_back(effect);
					EventRegisteror::GetInstance().CreateObject(effect, effect->GetType());
					CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::BOSS_SHAKE, 0.1f);
					CameraMgr::GetInstance().SetTrackingObject(mBossMonster);

				}

				else
				{
					mBoomCurTime += DT;
				}
			}

		}
	}

	


	
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

					mBossMonster = static_cast<Belial*>(
						MonsterFactory::CreateMonster<Belial>(MONSTER_TYPE::BOSS_BELIAL, Vec2(770, 900)));

					mBossMonster->Initialize();
					SceneMgr::GetInstance().GetCurScene()->AddGameObject(mBossMonster, mBossMonster->GetType());

					Vec2 bossMonsterPos = mBossMonster->GetPos();
					bossMonsterPos.y -= 65.f;

					CameraMgr::GetInstance().SetTrackingObject(nullptr);
					CameraMgr::GetInstance().SetLookPos(bossMonsterPos);

					GET_BOSS_APPEAR_HUD->SetBossMonster(mBossMonster);
					EventRegisteror::GetInstance().EnableHUD(HUD_TYPE::BOSS_APPEAR);
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
	for (int i = 0; i < mEffects.size(); ++i)
	{
		if (nullptr != mEffects[i])
		{
			delete mEffects[i];
			mEffects[i] = nullptr;
		}
	}
}

void BelialBossMap::Enter()
{
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::WALL, OBJECT_TYPE::MONSTER_EFFECT);
	BossMap::Enter();
}

void BelialBossMap::Exit()
{
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::WALL, OBJECT_TYPE::MONSTER_EFFECT);
	BossMap::Exit();


}
