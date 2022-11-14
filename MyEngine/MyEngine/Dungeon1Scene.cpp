#include "pch.h"
#include "Dungeon1Scene.h"
#include "CameraMgr.h"
#include "MouseMgr.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Player.h"
#include "EventRegisteror.h"

void Dungeon1Scene::Initialize()
{
	Scene::Initialize();
}

void Dungeon1Scene::Update()
{
	Scene::Update();
}

void Dungeon1Scene::Render()
{
	
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
	CameraMgr::GetInstance().RemoveEffect();
	CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::FADE_IN, 1.0f);

	Load(L"..\\Resource\\Map\\dungeon1.map");

	Player* player = new Player;
	player->SetPos(Vec2(TILE_SIZE * 10, TILE_SIZE * 20));
	player->Initialize();
	CameraMgr::GetInstance().SetTrackingObject(player);

	EventRegisteror::GetInstance().CreateObject(player, player->GetType());
}

void Dungeon1Scene::Exit()
{
}
