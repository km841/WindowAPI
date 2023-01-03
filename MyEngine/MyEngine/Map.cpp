#include "pch.h"
#include "Map.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "GameObject.h"
#include "LockedDoor.h"
#include "Player.h"
#include "CameraMgr.h"
#include "EventRegisteror.h"
#include "Stage.h"
#include "BossRoomGate.h"
#include "Sound.h"
#include "ResourceMgr.h"

Map::Map(const std::wstring& _path)
	: mInitDir(WARP_POINT::END)
	, mRegister(false)
	, mClear(false)
	, mVisit(false)
	, mChecked(false)
	, mPath(_path)
	, mAllowable(70.f)
	, mSound(nullptr)
{
	// 방향에 대한 정보
	// 그래프를 이용하는 방법
	// 4번째 방에 보스 방이 위치하도록 함
	mMapType = MAP_TYPE::NORMAL;
	mSound = LOAD_SOUND(L"LockDoorOpenSound", L"Sound\\LockDoorOpen.wav");

	size_t index = mPath.rfind(L'.');

	if (std::wstring::npos != index)
	{
		std::wstring dir = mPath.substr(0, index);
		
		size_t index = dir.rfind(L'_');
		
		std::wstring result = dir.substr(index + 1);

		for (int i = 0; i < result.size(); ++i)
		{
			switch (result[i])
			{
			case L'L':
				mPassages[(UINT)WARP_POINT::LEFT] = true;
				break;

			case L'R':
				mPassages[(UINT)WARP_POINT::RIGHT] = true;
				break;

			case L'T':
				mPassages[(UINT)WARP_POINT::TOP] = true;
				break;

			case L'B':
				mPassages[(UINT)WARP_POINT::BOTTOM] = true;
				break;
			}
		}
	}

}

Map::~Map()
{
}

void Map::Initialize()
{
	Scene* curScene = SceneMgr::GetInstance().GetCurScene();

	if (false == mClear)
	{
		curScene->Load(mPath);
	}

	else
	{
		GiveBackGameObject(OBJECT_TYPE::TILE);
		GiveBackGameObject(OBJECT_TYPE::TILE_BG);
		GiveBackGameObject(OBJECT_TYPE::WALL);
		GiveBackGameObject(OBJECT_TYPE::FOOTHOLD);
		GiveBackGameObject(OBJECT_TYPE::DUNGEON_OBJECT);
		GiveBackGameObject(OBJECT_TYPE::DROP_GOLD);
	}

	const std::vector<GameObject*>& dunObjVec = 
		SceneMgr::GetInstance().GetCurScene()->GetObjectGroup(OBJECT_TYPE::DUNGEON_OBJECT);

	for (int i = 0; i < dunObjVec.size(); ++i)
	{
		TOOL_ID id = dunObjVec[i]->GetToolID();
		switch (id)
		{
		case TOOL_ID::BTN_DOOR_0DEG:
			mEscapesPos[(UINT)WARP_POINT::BOTTOM] = dunObjVec[i]->GetPos();
			break;
		case TOOL_ID::BTN_DOOR_90DEG:
			mEscapesPos[(UINT)WARP_POINT::RIGHT] = dunObjVec[i]->GetPos();
			break;
		case TOOL_ID::BTN_DOOR_180DEG:
			mEscapesPos[(UINT)WARP_POINT::TOP] = dunObjVec[i]->GetPos();
			break;
		case TOOL_ID::BTN_DOOR_270DEG:
			mEscapesPos[(UINT)WARP_POINT::LEFT] = dunObjVec[i]->GetPos();
			break;

		case TOOL_ID::BTN_BELIAL_DOOR:
		case TOOL_ID::BTN_NIFLHEIM_DOOR:
		{
			if (MAP_TYPE::BOSS_SIDE == mMapType)
			{
				static_cast<BossRoomGate*>(dunObjVec[i])->SetDoorState(DOOR_STATE::CLOSE);
			}
		}
			break;
		}
	}
}

void Map::Update()
{
	const std::vector<GameObject*>& dunObjVec = 
		SceneMgr::GetInstance().GetCurScene()->GetObjectGroup(OBJECT_TYPE::DUNGEON_OBJECT);

	const std::vector<GameObject*>& evtObjVec =
		SceneMgr::GetInstance().GetCurScene()->GetObjectGroup(OBJECT_TYPE::EVENT_OBJECT);

	if (false == mClear && 
		(SceneMgr::GetInstance().GetCurScene()->AreAllObjectsDead(OBJECT_TYPE::MONSTER) &&
		evtObjVec.empty()))
	{
		for (int i = 0; i < dunObjVec.size(); ++i)
		{
			switch (dunObjVec[i]->GetToolID())
			{
			case TOOL_ID::BTN_DOOR_0DEG:
			case TOOL_ID::BTN_DOOR_90DEG:
			case TOOL_ID::BTN_DOOR_180DEG:
			case TOOL_ID::BTN_DOOR_270DEG:
				static_cast<LockedDoor*>(dunObjVec[i])->SetClearFlag(true);
				break;
			}
		}

		if (nullptr != mSound)
		{
			mSound->Play(false);
		}

		mClear = true;
	}

	if (mClear)
	{
		Player* player = Player::GetPlayer();

		if (nullptr != player)
		{
			
			Vec2 playerPos = player->GetPos();
			
			for (int i = 0; i < (UINT)WARP_POINT::END; ++i)
			{
				float distance = (playerPos - mEscapesPos[i]).Len();
				if (distance < mAllowable)
				{
					Map* nextMap = nullptr;
					switch ((WARP_POINT)i)
					{
					case WARP_POINT::LEFT:
						nextMap = mLinked[(UINT)WARP_POINT::LEFT];
						break;

					case WARP_POINT::RIGHT:
						nextMap = mLinked[(UINT)WARP_POINT::RIGHT];
						break;

					case WARP_POINT::TOP:
						nextMap = mLinked[(UINT)WARP_POINT::TOP];
						break;

					case WARP_POINT::BOTTOM:
						nextMap = mLinked[(UINT)WARP_POINT::BOTTOM];
						break;

					}

					if (nullptr != nextMap && 
						false == player->GetMoveMapCoolDown())
					{
						player->SetMoveMapCoolDown();
						EventRegisteror::GetInstance().TransitionToMap(mOwner, nextMap);
						nextMap->FromWhichInitDir((WARP_POINT)i);
					}
				}
			}

		}
	}

}

void Map::Render()
{
}

void Map::Destroy()
{
	for (int i = 0; i < (UINT)OBJECT_TYPE::END; ++i)
	{
		for (int j = 0; j < mMapObjects[i].size(); ++j)
		{
			if (nullptr != mMapObjects[i][j])
			{
				delete mMapObjects[i][j];
				mMapObjects[i][j] = nullptr;
			}
		}
	}
}

void Map::Enter()
{
	ShowCursor(false);
	CameraMgr::GetInstance().RemoveEffect();
	CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::FADE_IN, 1.0f);

	Initialize();

	const std::vector<GameObject*>& dunObjVec =
		SceneMgr::GetInstance().GetCurScene()->GetObjectGroup(OBJECT_TYPE::TILE);

	int widthMin = (int)21e8;
	int heightMin = (int)21e8;

	int widthMax = (int)-21e8;
	int heightMax = (int)-21e8;

	for (int i = 0; i < dunObjVec.size(); ++i)
	{
		Vec2 pos = dunObjVec[i]->GetPos();
		if (heightMax < pos.y)
			heightMax = (int)pos.y;

		if (heightMin > pos.y)
			heightMin = (int)pos.y;

		if (widthMax < pos.x)
			widthMax = (int)pos.x;

		if (widthMin > pos.x)
			widthMin = (int)pos.x;
	}

	CameraMgr::GetInstance().SetCameraLimitRect({ 
		widthMin - TILE_SIZE * 5,
		heightMin - TILE_SIZE * 5, 
		widthMax + TILE_SIZE * 5, 
		heightMax + TILE_SIZE * 5 });

	if (WARP_POINT::END == mInitDir)
	{

		Player* player = Player::GetPlayer();

		if (nullptr != player)
		{
			switch (mMapType)
			{
			case MAP_TYPE::NORMAL:
			{

				player->SetPos(mOwner->GetInitPlayerPos());
				player->SetStop(false);
				player->Initialize();

			}
			break;


			case MAP_TYPE::BOSS_SIDE:
			{
				std::vector<GameObject*>& dungeonObjVec = 
					SceneMgr::GetInstance().GetCurScene()->mObjects[(UINT)OBJECT_TYPE::DUNGEON_OBJECT];

				for (int i = 0; i < dungeonObjVec.size(); ++i)
				{
					if (TOOL_ID::BTN_BELIAL_DOOR == dungeonObjVec[i]->GetToolID() ||
						TOOL_ID::BTN_NIFLHEIM_DOOR == dungeonObjVec[i]->GetToolID())
					{
						player->SetPos(dungeonObjVec[i]->GetPos());
						break;
					}
				}
			}

			break;
			}
		}
	}

	else
	{
		switch (mInitDir)
		{
		case WARP_POINT::LEFT:
		{
			Vec2 objectPos = mEscapesPos[(UINT)WARP_POINT::RIGHT];
			objectPos.x -= TILE_SIZE;
			Player::GetPlayer()->SetPos(objectPos);
		}
			break;

		case WARP_POINT::RIGHT:
		{
			Vec2 objectPos = mEscapesPos[(UINT)WARP_POINT::LEFT];
			objectPos.x += TILE_SIZE;
			Player::GetPlayer()->SetPos(objectPos);
		}
			break;
			 
		case WARP_POINT::TOP:
		{
			Vec2 objectPos = mEscapesPos[(UINT)WARP_POINT::BOTTOM];
			objectPos.y -= TILE_SIZE;
			Player::GetPlayer()->SetPos(objectPos);
		}
			break;

		case WARP_POINT::BOTTOM:
		{
			Vec2 objectPos = mEscapesPos[(UINT)WARP_POINT::TOP];
			objectPos.y += TILE_SIZE;
			Player::GetPlayer()->SetPos(objectPos);
		}
			break;
		}
	}
}

void Map::Exit()
{
	//Player::GetPlayer()->AllCollisionExit();
	Scene* curScene = SceneMgr::GetInstance().GetCurScene();

	
	KeepGameObject(OBJECT_TYPE::TILE);
	KeepGameObject(OBJECT_TYPE::TILE_BG);
	KeepGameObject(OBJECT_TYPE::WALL);
	KeepGameObject(OBJECT_TYPE::FOOTHOLD);
	KeepGameObject(OBJECT_TYPE::DUNGEON_OBJECT);
	KeepGameObject(OBJECT_TYPE::DROP_GOLD);

	ShowCursor(true);
	//curScene->CleanObjectGroup(OBJECT_TYPE::PLAYER_EFFECT);
	//curScene->CleanObjectGroup(OBJECT_TYPE::MONSTER_EFFECT);
	//curScene->DeleteObjGroup(OBJECT_TYPE::EVENT_OBJECT);
	//curScene->DeleteObjGroup(OBJECT_TYPE::NPC);
	//curScene->DeleteObjGroup(OBJECT_TYPE::MISSILE_FROM_MONSTER);
	//curScene->DeleteObjGroup(OBJECT_TYPE::MISSILE_FROM_PLAYER);
	curScene->DeleteObjGroup(OBJECT_TYPE::PARTICLE);
	
	//curScene->CleanObjectGroup(OBJECT_TYPE::DUNGEON_OBJECT);
	//플레이어 충돌 전부 해제

	mClear = true;
}

void Map::SetMapLink(WARP_POINT _point, Map* _map)
{
	if (nullptr == _map)
		return;

	mLinked[(UINT)_point] = _map;

	bool reg = true;
	for (int i = 0; i < (UINT)WARP_POINT::END; ++i)
	{
		if (nullptr == mLinked[i])
			reg = false;
	}

	mRegister = reg;
}

void Map::KeepGameObject(OBJECT_TYPE _eType)
{
	std::vector<GameObject*>& objects = SceneMgr::GetInstance().GetCurScene()->mObjects[(UINT)_eType];
	mMapObjects[(UINT)_eType].insert(mMapObjects[(UINT)_eType].end(), objects.begin(), objects.end());
	SceneMgr::GetInstance().GetCurScene()->CleanObjectGroup(_eType);
}

void Map::GiveBackGameObject(OBJECT_TYPE _eType)
{
	std::vector<GameObject*>& objects = SceneMgr::GetInstance().GetCurScene()->mObjects[(UINT)_eType];

	for (int i = 0; i < mMapObjects[(UINT)_eType].size(); ++i)
	{
		objects.push_back(mMapObjects[(UINT)_eType][i]);
	}

	mMapObjects[(UINT)_eType].clear();
}

bool Map::IsDuplicationLink(Map* _map)
{
	for (int i = 0; i < (UINT)WARP_POINT::END; ++i)
	{
		if (GetMapLink((WARP_POINT)i) == _map)
		{
			return true;
		}
	}
	return false;
}

