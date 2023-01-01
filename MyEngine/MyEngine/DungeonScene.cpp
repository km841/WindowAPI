#include "pch.h"
#include "DungeonScene.h"
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
#include "Stage.h"
#include "Map.h"
#include "Prison.h"

DungeonScene::DungeonScene()
	: mClear(false)
	, mCurStage(nullptr)
{
	mSceneType = SCENE_TYPE::DUNGEON;
}

DungeonScene::~DungeonScene()
{
}

void DungeonScene::Initialize()
{
	Scene::Initialize();
	mStages[(UINT)STAGE_TYPE::PRISON] = new Prison;
	mCurStage = mStages[(UINT)STAGE_TYPE::PRISON];
}

void DungeonScene::Update()
{
	Scene::Update();

	if (nullptr != mCurStage)
	{
		mCurStage->Update();
	}
	
}

void DungeonScene::Render()
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

void DungeonScene::Destroy()
{
	Scene::Destroy();

	for (int i = 0; i < (UINT)STAGE_TYPE::END; ++i)
	{
		if (nullptr != mStages[i])
		{
			mStages[i]->Destroy();
			delete mStages[i];
			mStages[i] = nullptr;
		}
	}

}

void DungeonScene::Enter()
{
	mCurStage->Initialize();
	mCurStage->Enter();

	SetCollisionFlag();
}

void DungeonScene::Exit()
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
	// 스테이지 정리



}

void DungeonScene::SetCollisionFlag()
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
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MISSILE_FROM_MONSTER, OBJECT_TYPE::DUNGEON_OBJECT);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MISSILE_FROM_PLAYER, OBJECT_TYPE::MONSTER);

	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MONSTER, OBJECT_TYPE::PLAYER_EFFECT);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MONSTER, OBJECT_TYPE::WALL);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MONSTER, OBJECT_TYPE::FOOTHOLD);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MONSTER, OBJECT_TYPE::DUNGEON_OBJECT);
}

void DungeonScene::ChangeStage(STAGE_TYPE _type)
{
	if (nullptr != mCurStage)
	{
		mCurStage->Exit();
	}

	mCurStage = mStages[(UINT)_type];
	mCurStage->Enter();
}

