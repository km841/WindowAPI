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
	CameraMgr::GetInstance().RemoveEffect();
	CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::FADE_IN, 1.0f);

	Load(L"..\\Resource\\Map\\new_map2.map");
	Texture* townSky = ResourceMgr::GetInstance().Load<Texture>(L"TownSky", L"Texture\\TownSky.bmp");
	Texture* townBG = ResourceMgr::GetInstance().Load<Texture>(L"TownBG_Long", L"Texture\\TownBG_Long.bmp");
	Texture* treeBG = ResourceMgr::GetInstance().Load<Texture>(L"TreeBG_Long", L"Texture\\TreeBG_Long.bmp");
	Texture* floor = ResourceMgr::GetInstance().Load<Texture>(L"Floor", L"Texture\\Town_Floor.bmp");

	Player* player = new Player;
	player->SetPos(Vec2(TILE_SIZE * 35, TILE_SIZE * 20));
	player->Initialize();
	CameraMgr::GetInstance().SetTrackingObject(player);

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
	townTreeBg->SetPos(Vec2(200, 750));
	townTreeBg->SetPlayer(player);
	townTreeBg->SetTimes(TIMES);
	townTreeBg->SetSpeed(50.f);

	Structure* townFloor = new Structure;
	townFloor->SetPos(Vec2(TILE_SIZE * 50, TILE_SIZE * 20));
	townFloor->SetTexture(floor);
	townFloor->SetSize(floor->GetSize() * TIMES);

	//Wall* wall = new Wall;
	//wall->SetPos(Vec2(5000, TILE_SIZE * 20));
	//wall->SetSize(Vec2(10000, 30));

	InventoryUI* inven = 
		static_cast<InventoryUI*>(UIMgr::GetInstance().GetUI(UI_TYPE::INVENTORY));

	AddGameObject(townSkyBg, townSkyBg->GetType());
	AddGameObject(townForestBg, townForestBg->GetType());
	AddGameObject(townTreeBg, townTreeBg->GetType());
	AddGameObject(townFloor, townFloor->GetType());
	AddGameObject(player, player->GetType());
	//AddGameObject(wall, wall->GetType());
	AddGameObject(inven, inven->GetType());

	Initialize();
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::TILE);
}

void TownScene::Exit()
{
	DeleteObjGroup(OBJECT_TYPE::BACKGROUND_FIRST);
	DeleteObjGroup(OBJECT_TYPE::BACKGROUND_MIDDLE);
	DeleteObjGroup(OBJECT_TYPE::BACKGROUND_LAST);

}
