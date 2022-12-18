#include "pch.h"
#include "Dungeon2Scene.h"
#include "CameraMgr.h"
#include "MouseMgr.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Player.h"
#include "EventRegisteror.h"
#include "Collider.h"
#include "CollisionMgr.h"
#include "MonsterFactory.h"
#include "GiantSkullWarrior.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "ShortSword.h"
#include "GiantSkullSpawnEvent.h"
#include "RedGiantBatSpawnEvent.h"
#include "EventMgr.h"
#include "Wall.h"
#include "LockedDoor.h"

Dungeon2Scene::Dungeon2Scene()
{
	mSceneType = SCENE_TYPE::DUNGEON2;
}

Dungeon2Scene::~Dungeon2Scene()
{
}

void Dungeon2Scene::Initialize()
{
	DungeonScene::Initialize();
}

void Dungeon2Scene::Update()
{
	DungeonScene::Update();
}

void Dungeon2Scene::Render()
{
	DungeonScene::Render();
}

void Dungeon2Scene::Destroy()
{
	DungeonScene::Destroy();
}

void Dungeon2Scene::Enter()
{
	ShowCursor(false);
	CameraMgr::GetInstance().RemoveEffect();
	CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::FADE_IN, 1.0f);
	CameraMgr::GetInstance().SetCameraLimitRect({ 0, 0, WINDOW_WIDTH_SIZE + TILE_SIZE * 23, BOTTOM_LIMIT });

	Load(L"..\\Resource\\Map\\dungeon2.map");

	Player* player = Player::GetPlayer();
	if (nullptr != player)
	{
		player->SetPos(Vec2(TILE_SIZE * 5, GROUND_STANDARD));
		player->SetStop(false);
	}

	GiantSkullSpawnEvent* spawnEvent1 = new GiantSkullSpawnEvent;
	spawnEvent1->SetPos(Vec2(TILE_SIZE * 17, GROUND_STANDARD));
	spawnEvent1->SetSpawnPos(Vec2(TILE_SIZE * 17, TILE_SIZE * 15));

	GiantSkullSpawnEvent* spawnEvent2 = new GiantSkullSpawnEvent;
	spawnEvent2->SetPos(Vec2(TILE_SIZE * 22, GROUND_STANDARD));
	spawnEvent2->SetSpawnPos(Vec2(TILE_SIZE * 22, TILE_SIZE * 15));

	GiantSkullSpawnEvent* spawnEvent3 = new GiantSkullSpawnEvent;
	spawnEvent3->SetPos(Vec2(TILE_SIZE * 27, GROUND_STANDARD));
	spawnEvent3->SetSpawnPos(Vec2(TILE_SIZE * 27, TILE_SIZE * 15));

	RedGiantBatSpawnEvent* spawnEvent4 = new RedGiantBatSpawnEvent;
	spawnEvent4->SetPos(Vec2(TILE_SIZE * 32, GROUND_STANDARD));
	spawnEvent4->SetSpawnPos(Vec2(TILE_SIZE * 32, TILE_SIZE * 15));

	LockedDoor* lockDoor1 = new LockedDoor;
	lockDoor1->SetAngleType(ANGLE_TYPE::DEGREE_90_TYPE);
	lockDoor1->SetPos(Vec2(TILE_SIZE * 48.5f, (float)(GROUND_STANDARD - TILE_SIZE * 2)));

	LockedDoor* lockDoor2 = new LockedDoor;
	lockDoor2->SetAngleType(ANGLE_TYPE::DEGREE_270_TYPE);
	lockDoor2->SetPos(Vec2(TILE_SIZE * 1.5f, (float)(GROUND_STANDARD - TILE_SIZE * 2)));

	SceneMgr::GetInstance().GetCurScene()->AddGameObject(spawnEvent1, spawnEvent1->GetType());
	SceneMgr::GetInstance().GetCurScene()->AddGameObject(spawnEvent2, spawnEvent2->GetType());
	SceneMgr::GetInstance().GetCurScene()->AddGameObject(spawnEvent3, spawnEvent3->GetType());
	SceneMgr::GetInstance().GetCurScene()->AddGameObject(spawnEvent4, spawnEvent4->GetType());

	SceneMgr::GetInstance().GetCurScene()->AddGameObject(lockDoor1, lockDoor1->GetType());
	SceneMgr::GetInstance().GetCurScene()->AddGameObject(lockDoor2, lockDoor2->GetType());

	Initialize();

}

void Dungeon2Scene::Exit()
{
	CleanObjectGroup(OBJECT_TYPE::PLAYER_EFFECT);
	CleanObjectGroup(OBJECT_TYPE::MONSTER_EFFECT);
	DeleteObjGroup(OBJECT_TYPE::EVENT_OBJECT);
	DeleteObjGroup(OBJECT_TYPE::NPC);
	CleanObjectGroup(OBJECT_TYPE::WALL);
	CleanObjectGroup(OBJECT_TYPE::FOOTHOLD);
}
