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
#include "SoundMgr.h"
#include "Sound.h"
#include "ResourceMgr.h"

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
	, mSound(nullptr)
	, mAllDirBoomFlag(false)
	, mAllDirBoomMaxTime(0.15f)
	, mAllDirBoomCurTime(0.f)
	, mDistance(0.f)
	, mAllDirBoomMaxCount(12)
	, mAllDirBoomCurCount(0)
{
	mSound = LOAD_SOUND(L"MonsterDie", L"Sound\\MonsterDie.wav");

	mDirs.push_back(Vec2(-1, -1));
	mDirs.push_back(Vec2(0, -1));
	mDirs.push_back(Vec2(1, -1));
	mDirs.push_back(Vec2(1, 0));
	mDirs.push_back(Vec2(1, 1));
	mDirs.push_back(Vec2(0, 1));
	mDirs.push_back(Vec2(-1, 1));
	mDirs.push_back(Vec2(-1, 0));
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

	// Ű �Է��� �̿��� �������� ��ų ����

	if (nullptr != mBossMonster)
	{
		if (mBossMonster->IsDeadAnim())
		{
			// n�� ���

			if (mDeadStayMaxTime < mDeadStayCurTime)
			{
				// ����Ʈ ����
				// ���� ��ġ�� ���� ���� �������� ��������Ʈ
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
			if (false == mAllDirBoomFlag)
			{
				if (mBoomMaxCount < mBoomCurCount)
				{
					mAllDirBoomFlag = true;
					// ���� ����
					CameraMgr::GetInstance().SetTrackingObject(mBossMonster);
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

						EventRegisteror::GetInstance().CreateObject(effect, effect->GetType());
						mEffects.push_back(effect);


						if (nullptr != mSound)
							mSound->Play(false);

					}

					else
					{
						mBoomCurTime += DT;
					}
				}
			}

			else
			{

				if (mAllDirBoomMaxCount < mAllDirBoomCurCount)
				{
					//CameraMgr::GetInstance().SetLookPos(Player::GetPlayer()->GetPos());
					CameraMgr::GetInstance().SetTrackingObject(Player::GetPlayer());
					mBossMonster->SetObjState(OBJECT_STATE::DEAD);
					mBossMonster->GetEffect()->SetObjState(OBJECT_STATE::DEAD);
					EventRegisteror::GetInstance().DisableHUD(HUD_TYPE::BOSS_HP);
				}

				else
				{
					if (mAllDirBoomMaxTime < mAllDirBoomCurTime)
					{
						mAllDirBoomCurTime = 0.f;
						mAllDirBoomCurCount++;
						Vec2 bossPos = mBossMonster->GetPos();
						mDistance += 20.f;
						for (int i = 0; i < mDirs.size(); ++i)
						{
							BoomEffect* effect = new BoomEffect;
							Vec2 curPos = bossPos + mDirs[i] * mDistance;
							curPos += Vec2(30, -80);
							effect->SetPos(curPos);
							mEffects.push_back(effect);
							EventRegisteror::GetInstance().CreateObject(effect, effect->GetType());

							CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::BOSS_SHAKE, 0.1f);
							

							if (nullptr != mSound)
								mSound->Play(false);
						}
					}
					else
					{
						mAllDirBoomCurTime += DT;
					}
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
				// HUD ����
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

					Sound* belialLaugh = LOAD_SOUND(L"BelialLaugh", L"Sound\\BelialLaugh.wav");
					if (nullptr != belialLaugh)
					{
						belialLaugh->Play(false);
					}

					SoundMgr::GetInstance().ChangeBGM(LOAD_SOUND(L"PrisonBossBGM", L"Sound\\BelialThema.wav"));
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
