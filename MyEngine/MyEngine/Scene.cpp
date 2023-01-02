#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "Tile.h"
#include "ResourceMgr.h"
#include "Texture.h"
#include "Monster.h"
#include "Collider.h"
#include "MonsterSpawnEvent.h"
#include "GiantSkullWarrior.h"
#include "GiantBat.h"
#include "RedGiantBat.h"
#include "Banshee.h"
#include "Minotaur.h"
#include "BigGrayIceSkullWarrior.h"
#include "IceMage.h"
#include "Ovibos.h"
#include "CameraMgr.h"
#include "MouseMgr.h"
#include "LockedDoor.h"
#include "BelialRoomGate.h"
#include "NiflheimRoomGate.h"

Scene::Scene()
	: mOFN{}
	, mFileName{}
	, mDefaultTexture(nullptr)
{
	mOFN.lStructSize = sizeof(OPENFILENAME);
	mOFN.hwndOwner = APP_INSTANCE.GetHwnd();
	mOFN.lpstrFile = mFileName;
	mOFN.lpstrFilter = L"Map File\0*.map\0";
	mOFN.lpstrInitialDir = L"..\\Resource\\Map\\";
	mOFN.nMaxFile = sizeof(mFileName);
	mOFN.Flags = OFN_OVERWRITEPROMPT;
	mOFN.lpstrDefExt = L".map";
}

Scene::~Scene()
{
	for (size_t y = 0; (UINT)OBJECT_TYPE::END > y; ++y)
	{
		if (OBJECT_TYPE::PLAYER_EFFECT == (OBJECT_TYPE)y ||
			OBJECT_TYPE::MONSTER_EFFECT == (OBJECT_TYPE)y ||
			OBJECT_TYPE::UNIQUE_UI == (OBJECT_TYPE)y ||
			OBJECT_TYPE::FOOTHOLD == (OBJECT_TYPE)y ||
			OBJECT_TYPE::WALL == (OBJECT_TYPE)y ||
			OBJECT_TYPE::HUD == (OBJECT_TYPE)y)
		{
			continue;
		}

		for (size_t x = 0; mObjects[y].size() > x; ++x)
		{
			if (nullptr != mObjects[y][x])
			{
				delete mObjects[y][x];
				mObjects[y][x] = nullptr;
			}
		}
	}
}

void Scene::Initialize()
{
	for (size_t y = 0; (UINT)OBJECT_TYPE::END > y; ++y)
	{
		for (size_t x = 0; mObjects[y].size() > x; ++x)
		{
			if (nullptr != mObjects[y][x])
				mObjects[y][x]->Initialize();
		}
	}
}

void Scene::Update()
{
	for (size_t y = 0; (UINT)OBJECT_TYPE::END > y; ++y)
	{
		for (size_t x = 0; mObjects[y].size() > x; ++x)
		{
			if (mObjects[y][x]->IsDead())
				continue;
			
			if (nullptr != mObjects[y][x])
				mObjects[y][x]->Update();
		}
	}
}

void Scene::Render()
{
	for (size_t y = 0; (UINT)OBJECT_TYPE::END > y; ++y)
	{
		for (size_t x = 0; mObjects[y].size() > x; ++x)
		{
			if (mObjects[y][x]->IsDead())
				continue;

			if (nullptr != mObjects[y][x])
				mObjects[y][x]->Render();
		}
	}

}

void Scene::Destroy()
{
	for (size_t y = 0; (UINT)OBJECT_TYPE::END > y; ++y)
	{
		for (size_t x = 0; mObjects[y].size() > x; ++x)
		{
			if (nullptr != mObjects[y][x])
			{
				mObjects[y][x]->Destroy();
			}
		}
	}

}

void Scene::AddGameObject(GameObject* _obj, OBJECT_TYPE _eType)
{
	assert(_obj != nullptr);
	mObjects[(UINT)_eType].push_back(_obj);
}

void Scene::DeleteObjGroup(OBJECT_TYPE _eType)
{
	for (UINT i = 0; i < mObjects[(UINT)_eType].size(); ++i)
	{
		if (nullptr != mObjects[(UINT)_eType][i])
		{
			mObjects[(UINT)_eType][i]->Destroy();
			delete mObjects[(UINT)_eType][i];
			mObjects[(UINT)_eType][i] = nullptr;
		}
	}

	mObjects[(UINT)_eType].clear();
}

GameObject* Scene::GetNearestObject(GameObject* _src, OBJECT_TYPE _findType)
{
	GameObject* target = nullptr;
	float minDistance = 21e8;
	
	Vec2 srcPos = _src->GetPos();

	for (int i = 0; i < mObjects[(UINT)_findType].size(); ++i)
	{
		if (mObjects[(UINT)_findType][i]->IsDead())
			continue;

		Vec2 findTypePos = mObjects[(UINT)_findType][i]->GetPos();
		float distance = (srcPos - findTypePos).Len();
		if (minDistance > distance)
		{
			target = mObjects[(UINT)_findType][i];
			minDistance = distance;
		}
	}

	return target;
}

void Scene::FrameCorrection()
{
	Texture* tex = LOAD_TEXTURE(L"Collection", L"Texture\\CorrectionBmp.bmp");
	Vec2 size = tex->GetSize();
	TransparentBlt(
		BACK_BUF_DC,
		0, 0,
		(int)size.x,
		(int)size.y,
		tex->GetDC(),
		0, 0,
		(int)size.x,
		(int)size.y,
		RGB(255, 0, 255)
	);
}

bool Scene::AreAllObjectsDead(OBJECT_TYPE _eType)
{
	bool allDeadFlag = true;

	for (int i = 0; i < mObjects[(UINT)_eType].size(); ++i)
	{
		if (false == mObjects[(UINT)_eType][i]->IsDead())
			allDeadFlag = false;
	}

	return allDeadFlag;
}

void Scene::TileInitialize(size_t _size)
{
	std::vector<GameObject*>& tiles =  mObjects[(UINT)OBJECT_TYPE::TILE];
	for (int i = 0; i < _size; ++i)
	{
		tiles.push_back(new Tile);
	}
}

void Scene::Background_Black()
{
	Brush brush(BACK_BUF_DC, BRUSH_TYPE::DUNGEON_BLACK);
	Rectangle(BACK_BUF_DC,
		0, 0,
		WINDOW_WIDTH_SIZE,
		WINDOW_HEIGHT_SIZE);
}

void Scene::Background_White()
{
	Brush brush(BACK_BUF_DC, BRUSH_TYPE::WHITE);
	Rectangle(BACK_BUF_DC,
		0, 0,
		WINDOW_WIDTH_SIZE,
		WINDOW_HEIGHT_SIZE);
}

void Scene::Load(const std::wstring& _path)
{
	FILE* fp = nullptr;
	_wchdir(APP_INSTANCE.GetBaseAddress().c_str());
	errno_t error = _wfopen_s(&fp, _path.c_str(), L"rb");

	if (0 != error)
	{
		assert(nullptr);
	}

	DeleteObjGroup(OBJECT_TYPE::TILE);

	size_t tileSize = 0;
	fread(&tileSize, sizeof(size_t), 1, fp);

	TileInitialize(tileSize);

	std::vector<GameObject*>& tileGroup = mObjects[(UINT)OBJECT_TYPE::TILE];
	for (auto& tile : tileGroup)
	{
		dynamic_cast<Tile*>(tile)->Load(fp);
	}

	auto iter = tileGroup.begin();
	for (; iter != tileGroup.end(); )
	{
		Tile* tile = static_cast<Tile*>(*iter);
		if (TILE_TYPE::NONE == tile->GetTileType())
		{
			tile->SetType(OBJECT_TYPE::TILE_BG);
			mObjects[(UINT)OBJECT_TYPE::TILE_BG].push_back(std::move(*iter));
			iter = tileGroup.erase(iter);
		}

		else
		{
			iter++;
		}
	}

	size_t monsterSize = 0;
	fread(&monsterSize, sizeof(size_t), 1, fp);
	for (int i = 0; i < monsterSize; ++i)
	{
		Vec2 monsterPos = {};
		TOOL_ID id = {};

		fread(&monsterPos, sizeof(Vec2), 1, fp);
		fread(&id, sizeof(TOOL_ID), 1, fp);

		SetupMonster(id, monsterPos);
	}

	size_t dungeonObjSize = 0;
	fread(&dungeonObjSize, sizeof(size_t), 1, fp);
	for (int i = 0; i < dungeonObjSize; ++i)
	{
		Vec2 dungeonObjPos = {};
		TOOL_ID id = {};

		fread(&dungeonObjPos, sizeof(Vec2), 1, fp);
		fread(&id, sizeof(TOOL_ID), 1, fp);

		SetupDungeonObject(id, dungeonObjPos);
	}

	fclose(fp);
}

void Scene::SetupMonster(TOOL_ID _id, Vec2 _pos)
{
	switch (_id)
	{
	case TOOL_ID::BTN_RED_GIANT_BAT:
	{
		MonsterSpawnEvent<RedGiantBat>* spawnEvent = new MonsterSpawnEvent<RedGiantBat>;
		spawnEvent->SetPos(_pos);
		AddGameObject(spawnEvent, spawnEvent->GetType());
	}
	break;
	case TOOL_ID::BTN_GIANT_BAT:
	{
		MonsterSpawnEvent<GiantBat>* spawnEvent = new MonsterSpawnEvent<GiantBat>;
		spawnEvent->SetPos(_pos);
		AddGameObject(spawnEvent, spawnEvent->GetType());
	}
	break;
	case TOOL_ID::BTN_GIANT_SKULL:
	{
		MonsterSpawnEvent<GiantSkullWarrior>* spawnEvent = new MonsterSpawnEvent<GiantSkullWarrior>;
		spawnEvent->SetPos(_pos);
		AddGameObject(spawnEvent, spawnEvent->GetType());
	}
	break;
	case TOOL_ID::BTN_BANSHEE:
	{
		MonsterSpawnEvent<Banshee>* spawnEvent = new MonsterSpawnEvent<Banshee>;
		spawnEvent->SetPos(_pos);
		AddGameObject(spawnEvent, spawnEvent->GetType());
	}
	break;
	case TOOL_ID::BTN_ICE_GRAY_SKULL:
	{
		MonsterSpawnEvent<BigGrayIceSkullWarrior>* spawnEvent = new MonsterSpawnEvent<BigGrayIceSkullWarrior>;
		spawnEvent->SetPos(_pos);
		AddGameObject(spawnEvent, spawnEvent->GetType());
	}
	break;
	case TOOL_ID::BTN_MINOTAUR:
	{
		MonsterSpawnEvent<Minotaur>* spawnEvent = new MonsterSpawnEvent<Minotaur>;
		spawnEvent->SetPos(_pos);
		AddGameObject(spawnEvent, spawnEvent->GetType());
	}
	break;
	case TOOL_ID::BTN_ICE_MAGE:
	{
		MonsterSpawnEvent<IceMage>* spawnEvent = new MonsterSpawnEvent<IceMage>;
		spawnEvent->SetPos(_pos);
		AddGameObject(spawnEvent, spawnEvent->GetType());
	}
	break;
	case TOOL_ID::BTN_OVIBOS:
	{
		MonsterSpawnEvent<Ovibos>* spawnEvent = new MonsterSpawnEvent<Ovibos>;
		spawnEvent->SetPos(_pos);
		AddGameObject(spawnEvent, spawnEvent->GetType());
	}
	break;
	}
}

void Scene::SetupDungeonObject(TOOL_ID _id, Vec2 _pos)
{
	switch (_id)
	{
	case TOOL_ID::BTN_DOOR_0DEG:
	{
		LockedDoor* door = new LockedDoor;
		door->SetPos(_pos);
		door->SetAngleType(ANGLE_TYPE::DEGREE_0_TYPE);
		AddGameObject(door, door->GetType());
	}
	break;
	case TOOL_ID::BTN_DOOR_90DEG:
	{
		LockedDoor* door = new LockedDoor;
		door->SetPos(_pos);
		door->SetAngleType(ANGLE_TYPE::DEGREE_90_TYPE);
		AddGameObject(door, door->GetType());
	}
	break;
	case TOOL_ID::BTN_DOOR_180DEG:
	{
		LockedDoor* door = new LockedDoor;
		door->SetPos(_pos);
		door->SetAngleType(ANGLE_TYPE::DEGREE_180_TYPE);
		AddGameObject(door, door->GetType());
	}
	break;
	case TOOL_ID::BTN_DOOR_270DEG:
	{
		LockedDoor* door = new LockedDoor;
		door->SetPos(_pos);
		door->SetAngleType(ANGLE_TYPE::DEGREE_270_TYPE);
		AddGameObject(door, door->GetType());
	}
	break;
	case TOOL_ID::BTN_BELIAL_DOOR:
	{
		BelialRoomGate* door = new BelialRoomGate;
		door->SetPos(_pos);
		AddGameObject(door, door->GetType());
	}
	break;
	case TOOL_ID::BTN_NIFLHEIM_DOOR:
	{
		NiflheimRoomGate* door = new NiflheimRoomGate;
		door->SetPos(_pos);
		AddGameObject(door, door->GetType());
	}
	break;


	}
}
