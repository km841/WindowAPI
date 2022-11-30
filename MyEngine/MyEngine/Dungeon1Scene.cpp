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

void Dungeon1Scene::Initialize()
{
	Scene::Initialize();
}

void Dungeon1Scene::Update()
{
	Scene::Update();

	//Player* player = Player::GetPlayer();
	//if (nullptr != player)
	//{

	//	wchar_t szBuffer[256] = {};
	//	swprintf_s(szBuffer, L"playerX : %f, playerY : %f", player->GetPos().x, player->GetPos().y);
	//	SetWindowText(APP_INSTANCE.GetHwnd(), szBuffer);
	//}

	
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

void Dungeon1Scene::Enter()
{
	ShowCursor(false);
	CameraMgr::GetInstance().RemoveEffect();
	CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::FADE_IN, 1.0f);

	Load(L"..\\Resource\\Map\\dungeon1.map");

	Player* player = Player::GetPlayer();
	if (nullptr != player)
	{
		player->SetPos(Vec2(TILE_SIZE * 5,  TILE_SIZE * 20));
		player->SetStop(false);
		//ShortSword* sword = static_cast<ShortSword*>(player->GetEquipItem(EQUIP_TYPE::WEAPON_1));
		//AddGameObject(sword, sword->GetType());
	}

	Monster* skull1 = MonsterFactory::CreateMonster<GiantSkullWarrior>(MONSTER_TYPE::MELEE, Vec2(TILE_SIZE * 15, TILE_SIZE * 15));
	Monster* skull2 = MonsterFactory::CreateMonster<GiantSkullWarrior>(MONSTER_TYPE::MELEE, Vec2(TILE_SIZE * 20, TILE_SIZE * 15));
	Monster* skull3 = MonsterFactory::CreateMonster<GiantSkullWarrior>(MONSTER_TYPE::MELEE, Vec2(TILE_SIZE * 25, TILE_SIZE * 15));

	SceneMgr::GetInstance().GetCurScene()->AddGameObject(skull1, skull1->GetType());
	SceneMgr::GetInstance().GetCurScene()->AddGameObject(skull2, skull2->GetType());
	SceneMgr::GetInstance().GetCurScene()->AddGameObject(skull3, skull3->GetType());

	Initialize();
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::WALL);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MONSTER, OBJECT_TYPE::EFFECT);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::FOOTHOLD);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::NPC);

	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MONSTER, OBJECT_TYPE::WALL);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MONSTER, OBJECT_TYPE::FOOTHOLD);

}

void Dungeon1Scene::Exit()
{
	ShowCursor(true);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::WALL);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MONSTER, OBJECT_TYPE::EFFECT);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::FOOTHOLD);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::NPC);

	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MONSTER, OBJECT_TYPE::WALL);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::MONSTER, OBJECT_TYPE::FOOTHOLD);
}
