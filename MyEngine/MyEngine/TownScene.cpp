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
	CameraMgr::GetInstance().RemoveEffect();
	CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::FADE_IN, 1.0f);

	Load(L"..\\Resource\\Map\\new_map.map");
	Texture* townSky = ResourceMgr::GetInstance().Load<Texture>(L"TownSky", L"Texture\\TownSky.bmp");
	Texture* townBG = ResourceMgr::GetInstance().Load<Texture>(L"TownBG", L"Texture\\TownBG.bmp");
	Texture* floor = ResourceMgr::GetInstance().Load<Texture>(L"Floor", L"Texture\\Town_Floor.bmp");

	BackgroundUI* townSkyBg = new BackgroundUI;
	townSkyBg->SetTexture(townSky);
	townSkyBg->SetType(OBJECT_TYPE::BACKGROUND_FIRST);
	townSkyBg->SetSize(townSky->GetSize());

	BackgroundUI* townForestBg = new BackgroundUI;
	townForestBg->SetTexture(townBG);
	townForestBg->SetType(OBJECT_TYPE::BACKGROUND_MIDDLE);
	townForestBg->SetSize(townBG->GetSize());
	townForestBg->SetPos(Vec2(0, 100));

	Structure* townFloor = new Structure;
	townFloor->SetPos(Vec2(TILE_SIZE * 50, TILE_SIZE * 20));
	townFloor->SetTexture(floor);
	townFloor->SetSize(floor->GetSize() * 3);
	townFloor->SetType(OBJECT_TYPE::STRUCTURE);

	Player* player = new Player;
	player->SetPos(Vec2(TILE_SIZE * 35, TILE_SIZE * 20));
	player->Initialize();
	CameraMgr::GetInstance().SetTrackingObject(player);
	
	EventRegisteror::GetInstance().CreateObject(townSkyBg, townSkyBg->GetType());
	EventRegisteror::GetInstance().CreateObject(townForestBg, townForestBg->GetType());
	EventRegisteror::GetInstance().CreateObject(townFloor, townFloor->GetType());
	EventRegisteror::GetInstance().CreateObject(player, player->GetType());
}

void TownScene::Exit()
{
	DeleteObjGroup(OBJECT_TYPE::BACKGROUND_FIRST);
	DeleteObjGroup(OBJECT_TYPE::BACKGROUND_MIDDLE);
	DeleteObjGroup(OBJECT_TYPE::BACKGROUND_LAST);

}
