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
	}

	Initialize();
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::WALL);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::FOOTHOLD);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::NPC);
}

void Dungeon1Scene::Exit()
{
	ShowCursor(true);
}
