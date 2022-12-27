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

Map::Map(const std::wstring& _path)
	: mInitDir(WARP_POINT::END)
	, mRegister(false)
	, mClear(false)
	, mVisit(false)
	, mPath(_path)
{
	// ���⿡ ���� ����
	// �׷����� �̿��ϴ� ���
	// 4��° �濡 ���� ���� ��ġ�ϵ��� ��

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
		}
	}
}

void Map::Update()
{
	const std::vector<GameObject*>& dunObjVec = 
		SceneMgr::GetInstance().GetCurScene()->GetObjectGroup(OBJECT_TYPE::DUNGEON_OBJECT);

	const std::vector<GameObject*>& evtObjVec =
		SceneMgr::GetInstance().GetCurScene()->GetObjectGroup(OBJECT_TYPE::EVENT_OBJECT);

	if ((SceneMgr::GetInstance().GetCurScene()->AreAllObjectsDead(OBJECT_TYPE::MONSTER) &&
		evtObjVec.empty()))
	{
		for (int i = 0; i < dunObjVec.size(); ++i)
		{
			static_cast<LockedDoor*>(dunObjVec[i])->SetClearFlag(true);
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
				if (distance < 50.f)
				{
					Map* nextMap = nullptr;
					switch ((WARP_POINT)i)
					{
					case WARP_POINT::LEFT:
						nextMap = mLinked[(UINT)WARP_POINT::RIGHT];
						break;

					case WARP_POINT::RIGHT:
						nextMap = mLinked[(UINT)WARP_POINT::LEFT];
						break;

					case WARP_POINT::TOP:
						nextMap = mLinked[(UINT)WARP_POINT::BOTTOM];
						break;

					case WARP_POINT::BOTTOM:
						nextMap = mLinked[(UINT)WARP_POINT::TOP];
						break;

					}

					if (nullptr != nextMap)
					{
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
	int a = 0;
}

void Map::Enter()
{
	ShowCursor(false);
	CameraMgr::GetInstance().RemoveEffect();
	CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::FADE_IN, 1.0f);

	Initialize();

	const std::vector<GameObject*>& dunObjVec =
		SceneMgr::GetInstance().GetCurScene()->GetObjectGroup(OBJECT_TYPE::TILE);

	int btmMax = (int)-21e8;
	int rightMax = (int)-21e8;

	for (int i = 0; i < dunObjVec.size(); ++i)
	{
		Vec2 pos = dunObjVec[i]->GetPos();
		if (btmMax < pos.y)
			btmMax = (int)pos.y;

		if (rightMax < pos.x)
			rightMax = (int)pos.x;
	}

	CameraMgr::GetInstance().SetCameraLimitRect({ 0, 0, rightMax + TILE_SIZE, btmMax + TILE_SIZE });

	if (WARP_POINT::END == mInitDir)
	{
		Player* player = Player::GetPlayer();

		if (nullptr != player)
		{
			player->SetPos(mOwner->GetInitPlayerPos());
			player->SetStop(false);
			player->Initialize();
		}
	}

	else
	{
		switch (mInitDir)
		{
		case WARP_POINT::LEFT:
		{
			Vec2 objectPos = mEscapesPos[(UINT)WARP_POINT::RIGHT];
			objectPos.x += TILE_SIZE;
			Player::GetPlayer()->SetPos(objectPos);
		}
			break;

		case WARP_POINT::RIGHT:
		{
			Vec2 objectPos = mEscapesPos[(UINT)WARP_POINT::LEFT];
			objectPos.x -= TILE_SIZE;
			Player::GetPlayer()->SetPos(objectPos);
		}
			break;

		case WARP_POINT::TOP:
		{
			Vec2 objectPos = mEscapesPos[(UINT)WARP_POINT::BOTTOM];
			objectPos.y += TILE_SIZE;
			Player::GetPlayer()->SetPos(objectPos);
		}
			break;

		case WARP_POINT::BOTTOM:
		{
			Vec2 objectPos = mEscapesPos[(UINT)WARP_POINT::TOP];
			objectPos.y -= TILE_SIZE;
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

	ShowCursor(true);
	//curScene->CleanObjectGroup(OBJECT_TYPE::PLAYER_EFFECT);
	//curScene->CleanObjectGroup(OBJECT_TYPE::MONSTER_EFFECT);
	//curScene->DeleteObjGroup(OBJECT_TYPE::EVENT_OBJECT);
	//curScene->DeleteObjGroup(OBJECT_TYPE::NPC);
	curScene->DeleteObjGroup(OBJECT_TYPE::MISSILE_FROM_MONSTER);
	curScene->DeleteObjGroup(OBJECT_TYPE::MISSILE_FROM_PLAYER);
	curScene->DeleteObjGroup(OBJECT_TYPE::PARTICLE);
	
	//curScene->CleanObjectGroup(OBJECT_TYPE::DUNGEON_OBJECT);
	//�÷��̾� �浹 ���� ����

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

