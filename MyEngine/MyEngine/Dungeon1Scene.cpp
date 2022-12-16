#include "pch.h"
#include "Dungeon1Scene.h"
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
#include "UIMgr.h"
#include "InventoryUI.h"
#include "HPHUD.h"
#include "DashCountHUD.h"
#include "GiantBat.h"
#include "GiantBatSpawnEvent.h"
#include "NPCLineHUD.h"
#include "EquipedHUD.h"

Dungeon1Scene::Dungeon1Scene()
{
}

Dungeon1Scene::~Dungeon1Scene()
{
}

void Dungeon1Scene::Initialize()
{
	DungeonScene::Initialize();
}

void Dungeon1Scene::Update()
{
	DungeonScene::Update();

	Player* player = Player::GetPlayer();

	Vec2 pos = player->GetPos();

	if (pos.x > TILE_SIZE * 47.f)
	{
		EventRegisteror::GetInstance().ChangeScene(SCENE_TYPE::DUNGEON2);
	}

}

void Dungeon1Scene::Render()
{
	DungeonScene::Render();
}

void Dungeon1Scene::Destroy()
{
	DungeonScene::Destroy();
}

void Dungeon1Scene::Enter()
{
	ShowCursor(false);
	CameraMgr::GetInstance().RemoveEffect();
	CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::FADE_IN, 1.0f);
	CameraMgr::GetInstance().SetCameraLimitRect({ 0, 0, WINDOW_WIDTH_SIZE + TILE_SIZE * 21, BOTTOM_LIMIT });

	Load(L"..\\Resource\\Map\\dungeon1.map");

	//auto& events = EventMgr::GetInstance().GetEvents();

	Player* player = Player::GetPlayer();
	if (nullptr != player)
	{
		player->SetPos(Vec2(TILE_SIZE * 5,  GROUND_STANDARD));
		player->SetStop(false);
		//ShortSword* sword = static_cast<ShortSword*>(player->GetEquipItem(EQUIP_TYPE::WEAPON_1));
		//AddGameObject(sword, sword->GetType());
	}

	

	GiantSkullSpawnEvent* spawnEvent1 = new GiantSkullSpawnEvent;
	spawnEvent1->SetPos(Vec2(TILE_SIZE * 17, GROUND_STANDARD - TILE_SIZE  * 6));
	spawnEvent1->SetSpawnPos(Vec2(TILE_SIZE * 17, TILE_SIZE * 10));

	GiantSkullSpawnEvent* spawnEvent2 = new GiantSkullSpawnEvent;
	spawnEvent2->SetPos(Vec2(TILE_SIZE * 22, GROUND_STANDARD-TILE_SIZE * 6));
	spawnEvent2->SetSpawnPos(Vec2(TILE_SIZE * 22, TILE_SIZE * 10));

	GiantSkullSpawnEvent* spawnEvent3 = new GiantSkullSpawnEvent;
	spawnEvent3->SetPos(Vec2(TILE_SIZE * 27, GROUND_STANDARD-TILE_SIZE * 6));
	spawnEvent3->SetSpawnPos(Vec2(TILE_SIZE * 27, TILE_SIZE * 10));

	RedGiantBatSpawnEvent* spawnEvent4 = new RedGiantBatSpawnEvent;
	spawnEvent4->SetPos(Vec2(TILE_SIZE * 32, GROUND_STANDARD-TILE_SIZE * 6));
	spawnEvent4->SetSpawnPos(Vec2(TILE_SIZE * 32, TILE_SIZE * 15));

	GiantBatSpawnEvent* spawnEvent5 = new GiantBatSpawnEvent;
	spawnEvent5->SetPos(Vec2(TILE_SIZE * 37, GROUND_STANDARD - TILE_SIZE * 6));
	spawnEvent5->SetSpawnPos(Vec2(TILE_SIZE * 37, TILE_SIZE * 15));


	LockedDoor* lockDoor1 = new LockedDoor;
	lockDoor1->SetAngleType(ANGLE_TYPE::DEGREE_0_TYPE);
	lockDoor1->SetPos(Vec2(TILE_SIZE * 18, GROUND_STANDARD + (int)(TILE_SIZE * 1.5)));

	LockedDoor* lockDoor2 = new LockedDoor;
	lockDoor2->SetAngleType(ANGLE_TYPE::DEGREE_0_TYPE);
	lockDoor2->SetPos(Vec2(TILE_SIZE * 22, GROUND_STANDARD + (int)(TILE_SIZE * 1.5)));

	LockedDoor* lockDoor3 = new LockedDoor;
	lockDoor3->SetAngleType(ANGLE_TYPE::DEGREE_0_TYPE);
	lockDoor3->SetPos(Vec2(TILE_SIZE * 26, GROUND_STANDARD + (int)(TILE_SIZE * 1.5)));

	LockedDoor* lockDoor4 = new LockedDoor;
	lockDoor4->SetAngleType(ANGLE_TYPE::DEGREE_90_TYPE);
	lockDoor4->SetPos(Vec2(TILE_SIZE * 47.f, (float)(GROUND_STANDARD - TILE_SIZE * 8)));

	SceneMgr::GetInstance().GetCurScene()->AddGameObject(spawnEvent1, spawnEvent1->GetType());
	SceneMgr::GetInstance().GetCurScene()->AddGameObject(spawnEvent2, spawnEvent2->GetType());
	SceneMgr::GetInstance().GetCurScene()->AddGameObject(spawnEvent3, spawnEvent3->GetType());
	SceneMgr::GetInstance().GetCurScene()->AddGameObject(spawnEvent4, spawnEvent4->GetType());
	SceneMgr::GetInstance().GetCurScene()->AddGameObject(spawnEvent5, spawnEvent5->GetType());
	SceneMgr::GetInstance().GetCurScene()->AddGameObject(lockDoor1, lockDoor1->GetType());
	SceneMgr::GetInstance().GetCurScene()->AddGameObject(lockDoor2, lockDoor2->GetType());
	SceneMgr::GetInstance().GetCurScene()->AddGameObject(lockDoor3, lockDoor3->GetType());
	SceneMgr::GetInstance().GetCurScene()->AddGameObject(lockDoor4, lockDoor4->GetType());

	Initialize();
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::WALL);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::DROP_GOLD);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::DUNGEON_OBJECT);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::EVENT_OBJECT);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::MONSTER_EFFECT);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::FOOTHOLD);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::NPC);

	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::DROP_GOLD, OBJECT_TYPE::WALL);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::DROP_GOLD, OBJECT_TYPE::FOOTHOLD);

	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MISSILE_FROM_MONSTER, OBJECT_TYPE::WALL);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MISSILE_FROM_MONSTER, OBJECT_TYPE::FOOTHOLD);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MISSILE_FROM_MONSTER, OBJECT_TYPE::PLAYER);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MISSILE_FROM_PLAYER, OBJECT_TYPE::MONSTER);

	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MONSTER, OBJECT_TYPE::PLAYER_EFFECT);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MONSTER, OBJECT_TYPE::WALL);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MONSTER, OBJECT_TYPE::FOOTHOLD);
}

void Dungeon1Scene::Exit()
{
	ShowCursor(true);
	CleanObjectGroup(OBJECT_TYPE::PLAYER_EFFECT);
	CleanObjectGroup(OBJECT_TYPE::MONSTER_EFFECT);
	DeleteObjGroup(OBJECT_TYPE::EVENT_OBJECT);
	DeleteObjGroup(OBJECT_TYPE::NPC);
	CleanObjectGroup(OBJECT_TYPE::WALL);
	CleanObjectGroup(OBJECT_TYPE::FOOTHOLD);

	SceneMgr::GetInstance().TransfortObjects<GameObject*>(SCENE_TYPE::DUNGEON2,
		GET_INVENTORY_UI,
		GET_HP_HUD,
		GET_DASH_HUD,
		GET_NPCLINE_HUD,
		GET_EQUIPED_HUD,
		Player::GetPlayer());
}
