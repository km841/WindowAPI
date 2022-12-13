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

Dungeon1Scene::Dungeon1Scene()
	:mEnterFlag(false)
{
}

Dungeon1Scene::~Dungeon1Scene()
{
}

void Dungeon1Scene::Initialize()
{
	Scene::Initialize();
}

void Dungeon1Scene::Update()
{
	Scene::Update();

	// 던전 내 몬스터 개수
	if (mEnterFlag)
	{
		if (mObjects[(UINT)OBJECT_TYPE::MONSTER].empty() &&
			mObjects[(UINT)OBJECT_TYPE::EVENT_OBJECT].empty())
		{
			for (int i = 0; i < mObjects[(UINT)OBJECT_TYPE::DUNGEON_OBJECT].size(); ++i)
			{
				static_cast<LockedDoor*>(mObjects[(UINT)OBJECT_TYPE::DUNGEON_OBJECT][i])->SetClearFlag(true);
			}
		}
	}
}

void Dungeon1Scene::Render()
{
	Background_Black();
	Scene::Render();

	static Texture* aim
		= ResourceMgr::GetInstance().Load<Texture>(L"Aim", L"Texture\\Aim.bmp");
	Vec2 mousePos = MOUSE_POS;
	Vec2 aimSize = aim->GetSize();

	TransparentBlt(
		BACK_BUF_DC,
		(int)(mousePos.x - ((aimSize.x * TIMES) / 2.f)),
		(int)(mousePos.y - ((aimSize.y * TIMES) / 2.f)),
		(int)(aimSize.x * TIMES),
		(int)(aimSize.y * TIMES),
		aim->GetDC(),
		0, 0,
		(int)aimSize.x,
		(int)aimSize.y,
		RGB(255, 0, 255));
}

void Dungeon1Scene::Destroy()
{
	Scene::Destroy();
}

void Dungeon1Scene::Enter()
{
	ShowCursor(false);
	CameraMgr::GetInstance().RemoveEffect();
	CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::FADE_IN, 1.0f);

	Load(L"..\\Resource\\Map\\dungeon4.map");

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

	LockedDoor* lockDoor1 = new LockedDoor;
	lockDoor1->SetAngleType(ANGLE_TYPE::DEGREE_0_TYPE);
	lockDoor1->SetPos(Vec2(TILE_SIZE * 18, GROUND_STANDARD + (TILE_SIZE * 2)));

	LockedDoor* lockDoor2 = new LockedDoor;
	lockDoor2->SetAngleType(ANGLE_TYPE::DEGREE_0_TYPE);
	lockDoor2->SetPos(Vec2(TILE_SIZE * 22, GROUND_STANDARD + (TILE_SIZE * 2)));

	LockedDoor* lockDoor3 = new LockedDoor;
	lockDoor3->SetAngleType(ANGLE_TYPE::DEGREE_0_TYPE);
	lockDoor3->SetPos(Vec2(TILE_SIZE * 26, GROUND_STANDARD + (TILE_SIZE * 2)));

	LockedDoor* lockDoor4 = new LockedDoor;
	lockDoor4->SetAngleType(ANGLE_TYPE::DEGREE_90_TYPE);
	lockDoor4->SetPos(Vec2(TILE_SIZE * 47.5, (float)(GROUND_STANDARD - TILE_SIZE * 8)));

	SceneMgr::GetInstance().GetCurScene()->AddGameObject(spawnEvent1, spawnEvent1->GetType());
	SceneMgr::GetInstance().GetCurScene()->AddGameObject(spawnEvent2, spawnEvent2->GetType());
	SceneMgr::GetInstance().GetCurScene()->AddGameObject(spawnEvent3, spawnEvent3->GetType());
	SceneMgr::GetInstance().GetCurScene()->AddGameObject(spawnEvent4, spawnEvent4->GetType());
	SceneMgr::GetInstance().GetCurScene()->AddGameObject(lockDoor1, lockDoor1->GetType());
	SceneMgr::GetInstance().GetCurScene()->AddGameObject(lockDoor2, lockDoor2->GetType());
	SceneMgr::GetInstance().GetCurScene()->AddGameObject(lockDoor3, lockDoor3->GetType());
	SceneMgr::GetInstance().GetCurScene()->AddGameObject(lockDoor4, lockDoor4->GetType());

	Initialize();
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::WALL);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::DROP_GOLD);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::DUNGEON_OBJECT);

	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::DROP_GOLD, OBJECT_TYPE::WALL);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::DROP_GOLD, OBJECT_TYPE::FOOTHOLD);

	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::EVENT_OBJECT);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MONSTER, OBJECT_TYPE::PLAYER_EFFECT);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MISSILE_FROM_MONSTER, OBJECT_TYPE::WALL);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MISSILE_FROM_MONSTER, OBJECT_TYPE::FOOTHOLD);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MISSILE_FROM_MONSTER, OBJECT_TYPE::PLAYER);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MISSILE_FROM_PLAYER, OBJECT_TYPE::MONSTER);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::MONSTER_EFFECT);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::FOOTHOLD);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::NPC);

	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MONSTER, OBJECT_TYPE::WALL);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MONSTER, OBJECT_TYPE::FOOTHOLD);
	mEnterFlag = true;
}

void Dungeon1Scene::Exit()
{
	ShowCursor(true);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::WALL);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::DROP_GOLD);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::DUNGEON_OBJECT);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::DROP_GOLD, OBJECT_TYPE::WALL);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::DROP_GOLD, OBJECT_TYPE::FOOTHOLD);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::EVENT_OBJECT);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MONSTER, OBJECT_TYPE::PLAYER_EFFECT);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MISSILE_FROM_MONSTER, OBJECT_TYPE::WALL);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MISSILE_FROM_MONSTER, OBJECT_TYPE::FOOTHOLD);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MISSILE_FROM_MONSTER, OBJECT_TYPE::PLAYER);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MISSILE_FROM_PLAYER, OBJECT_TYPE::MONSTER);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::MONSTER_EFFECT);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::FOOTHOLD);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::NPC);

	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MONSTER, OBJECT_TYPE::WALL);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MONSTER, OBJECT_TYPE::FOOTHOLD);

	//DeleteObjGroup(OBJECT_TYPE::PLAYER);
	CleanObjectGroup(OBJECT_TYPE::PLAYER_EFFECT);
	CleanObjectGroup(OBJECT_TYPE::MONSTER_EFFECT);
	DeleteObjGroup(OBJECT_TYPE::EVENT_OBJECT);
	DeleteObjGroup(OBJECT_TYPE::NPC);
	CleanObjectGroup(OBJECT_TYPE::WALL);
	CleanObjectGroup(OBJECT_TYPE::FOOTHOLD);
	//DeleteObjGroup(OBJECT_TYPE::TILE);
}
