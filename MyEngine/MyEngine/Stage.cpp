#include "pch.h"
#include "Stage.h"
#include "Map.h"
#include "Player.h"
#include "BossMap.h"

Stage::Stage(STAGE_TYPE _type)
	: mBossSideMap(nullptr)
	, mBossMap(nullptr)
	, mCurMap(nullptr)
	, mStartMap(nullptr)
	, mStageType(_type)
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
	// 맵을 등록하고 Owner로 자신을 등록
}

void Stage::Update()
{
	if (nullptr != mCurMap)
	{
		mCurMap->Update();
	}
}

void Stage::Render()
{
}

void Stage::Destroy()
{
	for (int i = 0; i < mMaps.size(); ++i)
	{
		if (nullptr != mMaps[i])
		{
			mMaps[i]->Destroy();
			delete mMaps[i];
			mMaps[i] = nullptr;
		}
	}

	if (nullptr != mBossSideMap)
	{
		mBossSideMap->Destroy();
		delete mBossSideMap;
		mBossSideMap = nullptr;
	}

	if (nullptr != mBossMap)
	{
		mBossMap->Destroy();
		delete mBossMap;
		mBossMap = nullptr;
	}
}

void Stage::TransitionToMap(Map* _map)
{
	if (nullptr != mCurMap)
	{
		mCurMap->Exit();
	}
	
	mCurMap = _map;
	mCurMap->Enter();
}

void Stage::AddMap(const std::wstring& _path)
{
	Map* map = new Map(_path);
	map->SetOwnerStage(this);
	mMaps.push_back(map);
}

void Stage::ChainMaps(Map* _map)
{
	if (nullptr == _map || _map->GetVisit())
		return;

	_map->SetVisit();

	if (true == _map->IsPassage(WARP_POINT::LEFT) && 
		nullptr == _map->GetMapLink(WARP_POINT::LEFT))
	{
		for (int i = 0; i < mMaps.size(); ++i)
		{
			if (mMaps[i] == _map)
				continue;

			if (true == mMaps[i]->IsPassage(WARP_POINT::RIGHT) &&
				false == mMaps[i]->IsRegister() && 
				nullptr == mMaps[i]->GetMapLink(WARP_POINT::RIGHT))
			{
				mMaps[i]->SetMapLink(WARP_POINT::RIGHT, _map);
				_map->SetMapLink(WARP_POINT::LEFT, mMaps[i]);
				break;
			}
		}
	}

	if (true == _map->IsPassage(WARP_POINT::RIGHT) &&
		nullptr == _map->GetMapLink(WARP_POINT::RIGHT))
	{
		for (int i = 0; i < mMaps.size(); ++i)
		{
			if (mMaps[i] == _map)
				continue;

			if (true == mMaps[i]->IsPassage(WARP_POINT::LEFT) &&
				false == mMaps[i]->IsRegister() &&
				nullptr == mMaps[i]->GetMapLink(WARP_POINT::LEFT))
			{
				mMaps[i]->SetMapLink(WARP_POINT::LEFT, _map);
				_map->SetMapLink(WARP_POINT::RIGHT, mMaps[i]);
				break;
			}
		}
	}

	if (true == _map->IsPassage(WARP_POINT::TOP) && 
		nullptr == _map->GetMapLink(WARP_POINT::TOP))
	{
		for (int i = 0; i < mMaps.size(); ++i)
		{
			if (mMaps[i] == _map)
				continue;

			if (true == mMaps[i]->IsPassage(WARP_POINT::BOTTOM) &&
				false == mMaps[i]->IsRegister() &&
				nullptr == mMaps[i]->GetMapLink(WARP_POINT::BOTTOM))
			{
				mMaps[i]->SetMapLink(WARP_POINT::BOTTOM, _map);
				_map->SetMapLink(WARP_POINT::TOP, mMaps[i]);
				break;
			}
		}
	}

	if (true == _map->IsPassage(WARP_POINT::BOTTOM) && 
		nullptr == _map->GetMapLink(WARP_POINT::BOTTOM))
	{
		for (int i = 0; i < mMaps.size(); ++i)
		{
			if (mMaps[i] == _map)
				continue;

			if (true == mMaps[i]->IsPassage(WARP_POINT::TOP) &&
				false == mMaps[i]->IsRegister() &&
				nullptr == mMaps[i]->GetMapLink(WARP_POINT::TOP))
			{
				mMaps[i]->SetMapLink(WARP_POINT::TOP, _map);
				_map->SetMapLink(WARP_POINT::BOTTOM, mMaps[i]);
				break;
			}
		}
	}


	Map* temp = nullptr;
	for (int i = 0; i < (UINT)WARP_POINT::END; ++i)
	{
		temp = _map->GetMapLink((WARP_POINT)i);
		if (nullptr != temp)
			ChainMaps(temp);
	}
}

void Stage::SetBossSideMap(Map* _sideMap)
{
	
	mBossSideMap = _sideMap;
	mBossSideMap->SetOwnerStage(this);
	mBossSideMap->SetMapType(MAP_TYPE::BOSS_SIDE);

	if (nullptr != mBossMap && 
		nullptr == mBossMap->GetMapLink(WARP_POINT::LEFT))
	{
		mBossSideMap->SetMapLink(WARP_POINT::RIGHT, mBossMap);
		mBossMap->SetMapLink(WARP_POINT::LEFT, mBossSideMap);
	}
}

void Stage::SetBossMap(BossMap* _bossMap)
{
	mBossMap = _bossMap;
	mBossMap->SetOwnerStage(this);

	if (nullptr != mBossSideMap &&
		nullptr == mBossSideMap->GetMapLink(WARP_POINT::RIGHT))
	{
		mBossSideMap->SetMapLink(WARP_POINT::RIGHT, mBossMap);
		mBossMap->SetMapLink(WARP_POINT::LEFT, mBossSideMap);
	}
}
