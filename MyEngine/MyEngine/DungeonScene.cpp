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

DungeonScene::DungeonScene()
	:mClear(false)
{
}

DungeonScene::~DungeonScene()
{
}

void DungeonScene::Initialize()
{
	Scene::Initialize();
}

void DungeonScene::Update()
{
	Scene::Update();

	// 던전 내 몬스터 개수

	if (AreAllObjectsDead(OBJECT_TYPE::MONSTER) &&
		mObjects[(UINT)OBJECT_TYPE::EVENT_OBJECT].empty())
	{
		for (int i = 0; i < mObjects[(UINT)OBJECT_TYPE::DUNGEON_OBJECT].size(); ++i)
		{
			static_cast<LockedDoor*>(mObjects[(UINT)OBJECT_TYPE::DUNGEON_OBJECT][i])->SetClearFlag(true);
		}
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
}

