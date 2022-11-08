#include "pch.h"
#include "TownScene.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "BackgroundUI.h"
#include "EventRegisteror.h"
#include "Structure.h"
#include "Player.h"
#include "CameraMgr.h"

void TownScene::Initialize()
{
	
}

void TownScene::Update()
{
	Scene::Update();
}

void TownScene::Render()
{


	Scene::Render();
}

void TownScene::Enter()
{
	Load(L"..\\Resource\\Map\\new_map.map");
	Texture* townSky = ResourceMgr::GetInstance().Load<Texture>(L"TownSky", L"Texture\\TownSky.bmp");
	Texture* floor = ResourceMgr::GetInstance().Load<Texture>(L"Floor", L"Texture\\Town_Floor.bmp");

	BackgroundUI* townSkyBg = new BackgroundUI;
	townSkyBg->SetTexture(townSky);
	townSkyBg->SetType(OBJECT_TYPE::BACKGROUND_FIRST);
	townSkyBg->SetSize(townSky->GetSize());

	Structure* townFloor = new Structure;
	townFloor->SetPos(Vec2(TILE_SIZE * 50, TILE_SIZE * 20));
	townFloor->SetTexture(floor);
	townFloor->SetSize(floor->GetSize() * 3);
	townFloor->SetType(OBJECT_TYPE::STRUCTURE);

	Player* player = new Player;
	player->SetPos(Vec2(TILE_SIZE * 15, TILE_SIZE * 20));
	CameraMgr::GetInstance().SetTrackingObject(player);
	
	EventRegisteror::GetInstance().CreateObject(townSkyBg, townSkyBg->GetType());
	EventRegisteror::GetInstance().CreateObject(townFloor, townFloor->GetType());
	EventRegisteror::GetInstance().CreateObject(player, player->GetType());

	//CameraMgr::GetInstance().SetLookPos(Vec2(TILE_SIZE * 15, TILE_SIZE * 20));

}

void TownScene::Exit()
{
	DeleteObjGroup(OBJECT_TYPE::BACKGROUND_FIRST);
	DeleteObjGroup(OBJECT_TYPE::BACKGROUND_MIDDLE);
	DeleteObjGroup(OBJECT_TYPE::BACKGROUND_LAST);

}
