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
#include "DungeonEatEvent.h"
#include "SceneMgr.h"
#include "EventMgr.h"
#include "LineCollider.h"
#include "HPHUD.h"
#include "DashCountHUD.h"
#include "NPCLineHUD.h"
#include "EquipedHUD.h"
#include "ItemGetHUD.h"
#include "ItemInfoHUD.h"
#include "MinimapHUD.h"

TownScene::TownScene()
{
	mSceneType = SCENE_TYPE::TOWN;
}

TownScene::~TownScene()
{
}

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
	Brush brush(BACK_BUF_DC, BRUSH_TYPE::BLACK);
	Rectangle(
		BACK_BUF_DC,
		0, 0,
		WINDOW_WIDTH_SIZE,
		WINDOW_HEIGHT_SIZE
	);

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

void TownScene::Destroy()
{
	Scene::Destroy();
}

void TownScene::Enter()
{
	ShowCursor(false);
	CameraMgr::GetInstance().RemoveEffect();
	CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::FADE_IN, 1.0f);
	CameraMgr::GetInstance().SetCameraLimitRect({ 0, 0, WINDOW_WIDTH_SIZE + TILE_SIZE * 100, BOTTOM_LIMIT });

	Load(L"..\\Resource\\Map\\town.map");
	Texture* townSky = ResourceMgr::GetInstance().Load<Texture>(L"TownSky", L"Texture\\TownSky.bmp");
	Texture* townBG = ResourceMgr::GetInstance().Load<Texture>(L"TownBG_Long", L"Texture\\TownBG_Long.bmp");
	Texture* treeBG = ResourceMgr::GetInstance().Load<Texture>(L"TreeBG_Long", L"Texture\\TreeBG_Long.bmp");
	Texture* blackSmith = ResourceMgr::GetInstance().Load<Texture>(L"BlackSmith", L"Texture\\BlackSmith.bmp");
	Texture* tree01 = ResourceMgr::GetInstance().Load<Texture>(L"Tree01", L"Texture\\Tree01.bmp");
	Texture* tree02 = ResourceMgr::GetInstance().Load<Texture>(L"Tree02", L"Texture\\Tree02.bmp");
	Texture* grass01 = ResourceMgr::GetInstance().Load<Texture>(L"Grass01", L"Texture\\Grass01.bmp");
	Texture* grass02 = ResourceMgr::GetInstance().Load<Texture>(L"Grass02", L"Texture\\Grass02.bmp");
	Texture* grass03 = ResourceMgr::GetInstance().Load<Texture>(L"Grass03", L"Texture\\Grass03.bmp");

	Player* player = new Player;
	player->SetPos(Vec2(TILE_SIZE * 35, GROUND_STANDARD));
	//CameraMgr::GetInstance().SetLookPos(player->GetPos());
	CameraMgr::GetInstance().SetTrackingObject(player);


	BlackSmithNPC* blackSmithNPC = new BlackSmithNPC;
	blackSmithNPC->SetPos(Vec2(TILE_SIZE * 30, GROUND_STANDARD));
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
	townTreeBg->SetPos(Vec2(120, GROUND_STANDARD - TILE_SIZE * 4));
	townTreeBg->SetPlayer(player);
	townTreeBg->SetTimes(TIMES);
	townTreeBg->SetSpeed(50.f);

	UserFollowingBg* townTreeBg2 = new UserFollowingBg(true);
	townTreeBg2->SetTexture(treeBG);
	townTreeBg2->SetType(OBJECT_TYPE::BACKGROUND_LAST);
	townTreeBg2->SetSize(treeBG->GetSize() * TIMES);
	townTreeBg2->SetPos(Vec2(120 + (treeBG->GetSize().x * TIMES / 2.f), (float)GROUND_STANDARD - TILE_SIZE * 4));
	townTreeBg2->SetPlayer(player);
	townTreeBg2->SetTimes(TIMES);
	townTreeBg2->SetSpeed(50.f);

	Structure* blackSmithSt = new Structure;
	blackSmithSt->SetPos(Vec2(TILE_SIZE * 30, GROUND_STANDARD));
	blackSmithSt->SetTexture(blackSmith);
	blackSmithSt->SetSize(blackSmith->GetSize());

	Structure* Tree01St = new Structure;
	Tree01St->SetPos(Vec2(TILE_SIZE * 38, GROUND_STANDARD));
	Tree01St->SetTexture(tree01);
	Tree01St->SetSize(tree01->GetSize());

	Structure* Tree02St = new Structure;
	Tree02St->SetPos(Vec2(TILE_SIZE * 45, GROUND_STANDARD));
	Tree02St->SetTexture(tree02);
	Tree02St->SetSize(tree02->GetSize());

	Structure* Grass01St = new Structure;
	Grass01St->SetPos(Vec2(TILE_SIZE * 42, GROUND_STANDARD));
	Grass01St->SetTexture(grass01);
	Grass01St->SetSize(grass01->GetSize());

	Structure* Grass02St = new Structure;
	Grass02St->SetPos(Vec2(TILE_SIZE * 47, GROUND_STANDARD));
	Grass02St->SetTexture(grass02);
	Grass02St->SetSize(grass02->GetSize());

	Structure* Grass03St = new Structure;
	Grass03St->SetPos(Vec2(TILE_SIZE * 52, GROUND_STANDARD));
	Grass03St->SetTexture(grass03);
	Grass03St->SetSize(grass03->GetSize());

	Structure* Grass03St_2 = new Structure;
	Grass03St_2->SetPos(Vec2(TILE_SIZE * 35, GROUND_STANDARD));
	Grass03St_2->SetTexture(grass03);
	Grass03St_2->SetSize(grass03->GetSize());

	DungeonEatEvent* eatEvent = new DungeonEatEvent;
	eatEvent->SetPos(Vec2(TILE_SIZE * 70, GROUND_STANDARD));

	InventoryUI* inven = GET_INVENTORY_UI;
	HPHUD* hpHUD = GET_HP_HUD;
	DashCountHUD* dashHUD = GET_DASH_HUD;
	NPCLineHUD* npcLineHUD = GET_NPCLINE_HUD;
	EquipedHUD* equipedHUD = GET_EQUIPED_HUD;
	ItemGetHUD* itemGetHUD = GET_ITEMGET_HUD;
	ItemInfoHUD* itemInfoHUD = GET_ITEMINFO_HUD;
	MinimapHUD* minimapHUD = GET_MINIMAP_HUD;
	

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
	AddGameObject(Grass03St_2, Grass03St_2->GetType());

	AddGameObject(player, player->GetType());
	AddGameObject(blackSmithNPC, blackSmithNPC->GetType());
	AddGameObject(inven, inven->GetType());
	AddGameObject(hpHUD, hpHUD->GetType());
	AddGameObject(dashHUD, dashHUD->GetType());
	AddGameObject(equipedHUD, equipedHUD->GetType());
	AddGameObject(itemGetHUD, itemGetHUD->GetType());
	AddGameObject(npcLineHUD, npcLineHUD->GetType());
	AddGameObject(itemInfoHUD, itemInfoHUD->GetType());
	AddGameObject(minimapHUD, minimapHUD->GetType());
	AddGameObject(eatEvent, eatEvent->GetType());

	Initialize();
	SetCollisionFlag();
}

void TownScene::Exit()
{
	DeleteObjGroup(OBJECT_TYPE::BACKGROUND_FIRST);
	DeleteObjGroup(OBJECT_TYPE::BACKGROUND_MIDDLE);
	DeleteObjGroup(OBJECT_TYPE::BACKGROUND_LAST);
	DeleteObjGroup(OBJECT_TYPE::STRUCTURE);
	DeleteObjGroup(OBJECT_TYPE::EVENT_OBJECT);
	CleanObjectGroup(OBJECT_TYPE::PLAYER_EFFECT);
	CleanObjectGroup(OBJECT_TYPE::FOOTHOLD);
	CleanObjectGroup(OBJECT_TYPE::WALL);
	DeleteObjGroup(OBJECT_TYPE::TILE);
	DeleteObjGroup(OBJECT_TYPE::TILE_BG);
	
	//DeleteObjGroup(OBJECT_TYPE::TILE);
	//DeleteObjGroup(OBJECT_TYPE::EFFECT);


	SetCollisionFlag();

	SceneMgr::GetInstance().TransfortObjects<GameObject*>(SCENE_TYPE::DUNGEON1, 
															GET_INVENTORY_UI, 
															GET_HP_HUD, 
															GET_DASH_HUD,
															GET_EQUIPED_HUD,
															GET_NPCLINE_HUD,
															GET_ITEMGET_HUD,
															GET_ITEMINFO_HUD,
															GET_MINIMAP_HUD,
															Player::GetPlayer());

	Player::GetPlayer()->SetPrevScene(GetSceneType());
	ShowCursor(true);
}

void TownScene::SetCollisionFlag()
{
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::WALL);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::DROP_GOLD);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::DROP_ITEM);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::WALL, OBJECT_TYPE::DROP_ITEM);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::FOOTHOLD, OBJECT_TYPE::DROP_ITEM);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::FOOTHOLD);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::NPC);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::EVENT_OBJECT);
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::STRUCTURE);
}
