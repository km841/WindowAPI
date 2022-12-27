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
#include "EventMgr.h"
#include "Wall.h"
#include "LockedDoor.h"
#include "InventoryUI.h"
#include "HPHUD.h"
#include "DashCountHUD.h"
#include "NPCLineHUD.h"
#include "EquipedHUD.h"
#include "ItemGetHUD.h"
#include "ItemInfoHUD.h"
#include "MinimapHUD.h"
#include "MonsterSpawnEvent.h"
#include "GiantBat.h"
#include "RedGiantBat.h"
#include "Banshee.h"
#include "Minotaur.h"

Dungeon2Scene::Dungeon2Scene()
{
	//mSceneType = SCENE_TYPE::DUNGEON2;
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

	//Player* player = Player::GetPlayer();
	//Vec2 pos = player->GetPos();

	//if (pos.x < TILE_SIZE * 1.5f)
	//{
	//	EventRegisteror::GetInstance().ChangeScene(SCENE_TYPE::DUNGEON1);
	//	SceneMgr::GetInstance().TransfortObjects<GameObject*>(SCENE_TYPE::DUNGEON1,
	//		GET_INVENTORY_UI,
	//		GET_HP_HUD,
	//		GET_DASH_HUD,
	//		GET_NPCLINE_HUD,
	//		GET_EQUIPED_HUD,
	//		GET_ITEMGET_HUD,
	//		GET_ITEMINFO_HUD,
	//		GET_MINIMAP_HUD,
	//		Player::GetPlayer());
	//}

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

	Player* player = Player::GetPlayer();
	if (nullptr != player)
	{
		player->SetPos(Vec2(TILE_SIZE * 2, GROUND_STANDARD));
		player->SetStop(false);
	}

	if (false == mClear)
	{
		Load(L"..\\Resource\\Map\\dungeon2.map");
	}

	Initialize();
	SetCollisionFlag();
}

void Dungeon2Scene::Exit()
{
	CleanObjectGroup(OBJECT_TYPE::PLAYER_EFFECT);
	CleanObjectGroup(OBJECT_TYPE::MONSTER_EFFECT);
	DeleteObjGroup(OBJECT_TYPE::EVENT_OBJECT);
	DeleteObjGroup(OBJECT_TYPE::NPC);
	DeleteObjGroup(OBJECT_TYPE::MISSILE_FROM_MONSTER);
	DeleteObjGroup(OBJECT_TYPE::MISSILE_FROM_PLAYER);
	DeleteObjGroup(OBJECT_TYPE::PARTICLE);
	CleanObjectGroup(OBJECT_TYPE::WALL);
	CleanObjectGroup(OBJECT_TYPE::FOOTHOLD);

	SetCollisionFlag();

	Player::GetPlayer()->SetPrevScene(GetSceneType());
	mClear = true;
}



void Dungeon2Scene::SetCollisionFlag()
{
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::WALL);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::DROP_GOLD);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::DUNGEON_OBJECT);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::EVENT_OBJECT);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::MONSTER_EFFECT);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::MONSTER);
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
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MONSTER, OBJECT_TYPE::DUNGEON_OBJECT);
}
