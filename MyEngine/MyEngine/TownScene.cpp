#include "pch.h"
#include "TownScene.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "InfRepeatBg.h"
#include "EventRegisteror.h"
#include "Structure.h"
#include "Player.h"
#include "CameraMgr.h"
#include "UserFollowingBg.h"
#include "MouseMgr.h"
#include "Wall.h"
#include "CollisionMgr.h"
#include "InventoryUI.h"
#include "ShortSword.h"
#include "UIMgr.h"
#include "KeyMgr.h"
#include "BlackSmithNPC.h"

void TownScene::Initialize()
{
	Scene::Initialize();
}

void TownScene::Update()
{

	Scene::Update();
}

void TownScene::Render()
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

void TownScene::Enter()
{
	ShowCursor(false);
	CameraMgr::GetInstance().RemoveEffect();
	CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::FADE_IN, 1.0f);

	Load(L"..\\Resource\\Map\\map4.map");
	Texture* townSky = ResourceMgr::GetInstance().Load<Texture>(L"TownSky", L"Texture\\TownSky.bmp");
	Texture* townBG = ResourceMgr::GetInstance().Load<Texture>(L"TownBG_Long", L"Texture\\TownBG_Long.bmp");
	Texture* treeBG = ResourceMgr::GetInstance().Load<Texture>(L"TreeBG_Long", L"Texture\\TreeBG_Long.bmp");
	Texture* blackSmith = ResourceMgr::GetInstance().Load<Texture>(L"BlackSmith", L"Texture\\BlackSmith.bmp");
	Texture* tree01 = ResourceMgr::GetInstance().Load<Texture>(L"Tree01", L"Texture\\Tree01.bmp");
	Texture* tree02 = ResourceMgr::GetInstance().Load<Texture>(L"Tree02", L"Texture\\Tree02.bmp");
	Texture* grass01 = ResourceMgr::GetInstance().Load<Texture>(L"Grass01", L"Texture\\Grass01.bmp");
	Texture* grass02 = ResourceMgr::GetInstance().Load<Texture>(L"Grass02", L"Texture\\Grass02.bmp");
	Texture* grass03 = ResourceMgr::GetInstance().Load<Texture>(L"Grass03", L"Texture\\Grass03.bmp");

	//Texture* floorPixel = ResourceMgr::GetInstance().Load<Texture>(L"Floor_Pixel", L"Texture\\BlackSmith.bmp");

	Player* player = new Player;
	player->SetPos(Vec2(TILE_SIZE * 35, TILE_SIZE * 20));
	player->Initialize();
	CameraMgr::GetInstance().SetTrackingObject(player);

	BlackSmithNPC* blackSmithNPC = new BlackSmithNPC;
	blackSmithNPC->SetPos(Vec2(TILE_SIZE * 30, TILE_SIZE * 20));
	blackSmithNPC->Initialize();

	InfRepeatBg* townSkyBg = new InfRepeatBg;
	townSkyBg->SetTexture(townSky);
	townSkyBg->SetType(OBJECT_TYPE::BACKGROUND_FIRST);
	townSkyBg->SetSize(townSky->GetSize());

	UserFollowingBg* townForestBg = new UserFollowingBg(false);
	townForestBg->SetTexture(townBG);
	townForestBg->SetType(OBJECT_TYPE::BACKGROUND_MIDDLE);
	townForestBg->SetSize(townBG->GetSize());
	townForestBg->SetPos(Vec2(-500, 100));
	townForestBg->SetPlayer(player);
	townForestBg->SetSpeed(15.f);

	UserFollowingBg* townTreeBg = new UserFollowingBg(true);
	townTreeBg->SetTexture(treeBG);
	townTreeBg->SetType(OBJECT_TYPE::BACKGROUND_LAST);
	townTreeBg->SetSize(treeBG->GetSize() * TIMES);
	townTreeBg->SetPos(Vec2(120, 750));
	townTreeBg->SetPlayer(player);
	townTreeBg->SetTimes(TIMES);
	townTreeBg->SetSpeed(50.f);

	UserFollowingBg* townTreeBg2 = new UserFollowingBg(true);
	townTreeBg2->SetTexture(treeBG);
	townTreeBg2->SetType(OBJECT_TYPE::BACKGROUND_LAST);
	townTreeBg2->SetSize(treeBG->GetSize() * TIMES);
	townTreeBg2->SetPos(Vec2(120 + (treeBG->GetSize().x * TIMES / 2.f), 750.f));
	townTreeBg2->SetPlayer(player);
	townTreeBg2->SetTimes(TIMES);
	townTreeBg2->SetSpeed(50.f);

	Structure* blackSmithSt = new Structure;
	blackSmithSt->SetPos(Vec2(TILE_SIZE * 30, TILE_SIZE * 20));
	blackSmithSt->SetTexture(blackSmith);
	blackSmithSt->SetSize(blackSmith->GetSize());

	Structure* Tree01St = new Structure;
	Tree01St->SetPos(Vec2(TILE_SIZE * 38, TILE_SIZE * 20));
	Tree01St->SetTexture(tree01);
	Tree01St->SetSize(tree01->GetSize());

	Structure* Tree02St = new Structure;
	Tree02St->SetPos(Vec2(TILE_SIZE * 45, TILE_SIZE * 20));
	Tree02St->SetTexture(tree02);
	Tree02St->SetSize(tree02->GetSize());

	Structure* Grass01St = new Structure;
	Grass01St->SetPos(Vec2(TILE_SIZE * 42, TILE_SIZE * 20));
	Grass01St->SetTexture(grass01);
	Grass01St->SetSize(grass01->GetSize());

	Structure* Grass02St = new Structure;
	Grass02St->SetPos(Vec2(TILE_SIZE * 47, TILE_SIZE * 20));
	Grass02St->SetTexture(grass02);
	Grass02St->SetSize(grass02->GetSize());

	Structure* Grass03St = new Structure;
	Grass03St->SetPos(Vec2(TILE_SIZE * 52, TILE_SIZE * 20));
	Grass03St->SetTexture(grass03);
	Grass03St->SetSize(grass03->GetSize());

	//Wall* wall = new Wall;
	//wall->SetPos(Vec2(5000, TILE_SIZE * 20));
	//wall->SetSize(Vec2(10000, 30));

	InventoryUI* inven = 
		static_cast<InventoryUI*>(UIMgr::GetInstance().GetUI(UI_TYPE::INVENTORY));

	AddGameObject(townSkyBg, townSkyBg->GetType());
	AddGameObject(townForestBg, townForestBg->GetType());

	AddGameObject(townTreeBg, townTreeBg->GetType());
	AddGameObject(townTreeBg2, townTreeBg2->GetType());

	AddGameObject(blackSmithSt, blackSmithSt->GetType());
	AddGameObject(Tree01St, Tree01St->GetType());
	AddGameObject(Tree02St, Tree02St->GetType());

	AddGameObject(Grass01St, Grass01St->GetType());
	AddGameObject(Grass02St, Grass02St->GetType());
	AddGameObject(Grass03St, Grass03St->GetType());

	AddGameObject(player, player->GetType());
	AddGameObject(blackSmithNPC, blackSmithNPC->GetType());
	AddGameObject(inven, inven->GetType());

	Initialize();
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::TILE);
}

void TownScene::Exit()
{
	DeleteObjGroup(OBJECT_TYPE::BACKGROUND_FIRST);
	DeleteObjGroup(OBJECT_TYPE::BACKGROUND_MIDDLE);
	DeleteObjGroup(OBJECT_TYPE::BACKGROUND_LAST);
	ShowCursor(true);
}
