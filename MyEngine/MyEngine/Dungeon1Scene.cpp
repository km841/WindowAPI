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
#include "SceneMgr.h"
#include "Scene.h"
#include "ShortSword.h"
#include "EventMgr.h"
#include "Wall.h"
#include "LockedDoor.h"
#include "UIMgr.h"
#include "InventoryUI.h"
#include "HPHUD.h"
#include "DashCountHUD.h"
#include "NPCLineHUD.h"
#include "EquipedHUD.h"
#include "ItemGetHUD.h"
#include "ItemInfoHUD.h"
#include "MinimapHUD.h"
#include "MonsterSpawnEvent.h"
#include "GiantSkullWarrior.h"
#include "GiantBat.h"
#include "RedGiantBat.h"
#include "Banshee.h"
#include "Minotaur.h"
#include "BigGrayIceSkullWarrior.h"
#include "IceMage.h"
#include "Ovibos.h"

Dungeon1Scene::Dungeon1Scene()
{
	mSceneType = SCENE_TYPE::DUNGEON1;
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
	CameraMgr::GetInstance().SetCameraLimitRect({ 0, 0, WINDOW_WIDTH_SIZE + TILE_SIZE * 21, BOTTOM_LIMIT});

	Player* player = Player::GetPlayer();
	if (nullptr != player)
	{
		switch (player->GetPrevScene())
		{
		case SCENE_TYPE::TOWN:
			player->SetPos(Vec2(TILE_SIZE * 5, GROUND_STANDARD));
			break;

		case SCENE_TYPE::DUNGEON2:
			player->SetPos(Vec2(TILE_SIZE * 46.f, (float)(GROUND_STANDARD - TILE_SIZE * 6)));
			break;
		}
		
		player->SetStop(false);
	}

	if (false == mClear)
	{
		Load(L"..\\Resource\\Map\\dungeon4.map");
	}

	Initialize();
	SetCollisionFlag();
}

void Dungeon1Scene::Exit()
{
	ShowCursor(true);
	CleanObjectGroup(OBJECT_TYPE::PLAYER_EFFECT);
	CleanObjectGroup(OBJECT_TYPE::MONSTER_EFFECT);
	DeleteObjGroup(OBJECT_TYPE::EVENT_OBJECT);
	DeleteObjGroup(OBJECT_TYPE::NPC);
	DeleteObjGroup(OBJECT_TYPE::MISSILE_FROM_MONSTER);
	DeleteObjGroup(OBJECT_TYPE::MISSILE_FROM_PLAYER);
	DeleteObjGroup(OBJECT_TYPE::PARTICLE);
	CleanObjectGroup(OBJECT_TYPE::WALL);
	CleanObjectGroup(OBJECT_TYPE::FOOTHOLD);

	SceneMgr::GetInstance().TransfortObjects<GameObject*>(SCENE_TYPE::DUNGEON2,
		GET_INVENTORY_UI,
		GET_HP_HUD,
		GET_DASH_HUD,
		GET_NPCLINE_HUD,
		GET_EQUIPED_HUD,
		GET_ITEMGET_HUD,
		GET_ITEMINFO_HUD,
		GET_MINIMAP_HUD,
		Player::GetPlayer());


	SetCollisionFlag();
	Player::GetPlayer()->SetPrevScene(GetSceneType());
	mClear = true;
}

void Dungeon1Scene::SetCollisionFlag()
{
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::WALL);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::DROP_GOLD);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::EVENT_OBJECT);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::DUNGEON_OBJECT);
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
