#include "pch.h"
#include "ToolScene.h"
#include "ResourceMgr.h"
#include "ToolUI.h"
#include "Texture.h"
#include "EventRegisteror.h"
#include "CameraMgr.h"
#include "IconUI.h"
#include "MouseMgr.h"
#include "Tile.h"
#include "CheckButtonUI.h"
#include "KeyMgr.h"
#include "Wall.h"
#include "Foothold.h"
#include "SceneMgr.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "LineCollider.h"
#include "ToolWindows.h"
#include "MonsterSpawnEvent.h"
#include "GiantSkullWarrior.h"
#include "GiantBat.h"
#include "RedGiantBat.h"
#include "Banshee.h"
#include "Minotaur.h"
#include "BigGrayIceSkullWarrior.h"
#include "IceMage.h"
#include "Ovibos.h"

ToolScene::ToolScene()
	: mCheckedObjectType(OBJECT_TYPE::TILE_BG)
	, mCheckedTileType(TILE_TYPE::NONE)
{
	mSceneType = SCENE_TYPE::TOOL;
}

ToolScene::~ToolScene()
{
}

void ToolScene::Initialize()
{
	mDefaultTexture = ResourceMgr::GetInstance().Load<Texture>(L"TileMap", L"Texture\\Map3.bmp");
	assert(mDefaultTexture);

	mBlendFunc = {};
	mBlendFunc.BlendFlags = 0;
	mBlendFunc.AlphaFormat = AC_SRC_ALPHA;
	mBlendFunc.BlendOp = AC_SRC_OVER;
	mBlendFunc.SourceConstantAlpha = 127;

	Scene::Initialize();
}

void ToolScene::Update()
{
	if (OBJECT_TYPE::TILE_BG == mCheckedObjectType)
	{
		mCheckedTileType = TILE_TYPE::NONE;
		CheckMenuRadioItem(APP_INSTANCE.GetColMenuHandle(), 0, 2, 2, MF_BYPOSITION);
	}

	IconUI* selectedUI = IconUI::GetSelectedUI();
	CheckButtonUI* checkedUI = CheckButtonUI::GetCheckedButton();
	Vec2 mousePos = WORLD_POS(MOUSE_POS);
	Vec2 tilePos = CameraMgr::GetInstance().GetTileCoord(mousePos);

	mCurToolID = TOOL_INSTANCE.GetSelectedID();

	if (IsTileableArea(tilePos))
	{
		if (nullptr != checkedUI)
		{
			if (checkedUI->GetIndex())
			{
				if (IS_JUST_LBUTTON_CLICKED)
				{
					SetupTile();
				}
			}

			else
			{
				if (IS_LBUTTON_CLICKED)
				{
					SetupTile();
				}
			}
		}

		if (TOOL_ID::END != mCurToolID)
		{
			// 클릭한 위치에 SpawnObject가 있어야 함
			// 위치, 몬스터가 맵에 저장되어야 하며... 
			// 클릭한 순간 그걸 보유한 뭔가가 맵에 만들어져야 함
			if (IS_JUST_LBUTTON_CLICKED)
			{
				if (TOOL_ID::BTN_OVIBOS >= mCurToolID)
				{
					SetupMonster(mCurToolID, WORLD_POS(MOUSE_POS));
				}
				else
				{
					Vec2 pos = WORLD_POS(MOUSE_POS);
					pos = CameraMgr::GetInstance().GetTileCoord(pos);
					switch (mCurToolID)
					{
					case TOOL_ID::BTN_DOOR_0DEG:
					case TOOL_ID::BTN_DOOR_180DEG:
						pos.y += TILE_OFFSET;
						pos.x += TILE_SIZE * 2.f;
						break;

					case TOOL_ID::BTN_DOOR_90DEG:
					case TOOL_ID::BTN_DOOR_270DEG:
						pos.x += TILE_OFFSET;
						pos.y += TILE_SIZE * 2.f;
						break;
					}

					SetupDungeonObject(mCurToolID, pos);
				}
				
			}


		}
	}

	if (IS_RBUTTON_CLICKED)
	{
		RemoveTile(tilePos);
		TOOL_INSTANCE.AllButtonRelease();
	}
	

	if (IS_PRESSED(KEY::LCTRL) && IS_JUST_PRESSED(KEY::S))
	{
		Save();
	}

	if (IS_PRESSED(KEY::LCTRL) && IS_JUST_PRESSED(KEY::O))
	{
		Load();
	}

	if (IS_PRESSED(KEY::BACKSPACE))
	{
		TOOL_INSTANCE.AllButtonRelease();
		EventRegisteror::GetInstance().ChangeScene(SCENE_TYPE::TITLE);
	}


	for (size_t y = 0; (UINT)OBJECT_TYPE::END > y; ++y)
	{
		for (size_t x = 0; mObjects[y].size() > x; ++x)
		{
			if (mObjects[y][x]->IsDead())
				continue;

			if (y == (UINT)OBJECT_TYPE::MONSTER)
				continue;

			if (nullptr != mObjects[y][x])
				mObjects[y][x]->Update();
		}
	}
}

void ToolScene::Render()
{	
	AuxLineRender();
	Scene::Render();
	GuideCircle();
	GuideText();


	// 블럭이 클릭되었을 때의 이벤트
	IconUI* selectedUI = IconUI::GetSelectedUI();
	if (nullptr != selectedUI)
	{
		Vec2 ltPos = selectedUI->GetLTPos();
		Vec2 mousePos = MOUSE_POS;

		AlphaBlend(
			BACK_BUF_DC,
			(int)(mousePos.x - TILE_SIZE / 2),
			(int)(mousePos.y - TILE_SIZE / 2),
			TILE_SIZE,
			TILE_SIZE,
			mDefaultTexture->GetDC(),
			(int)(ltPos.x),
			(int)(ltPos.y),
			IMAGE_TILE_SIZE_X,
			IMAGE_TILE_SIZE_Y,
			mBlendFunc
		);
	}

	if (TOOL_ID::END == mCurToolID)
		return;

	ButtonInfo btnInfo = TOOL_INSTANCE.GetButtonInfo(mCurToolID);
	Texture* btnTex = nullptr; 

	switch (mCurToolID)
	{
	case TOOL_ID::BTN_RED_GIANT_BAT:
		btnTex = ResourceMgr::GetInstance().Load<Texture>(L"RED_GIANT_BAT_SAMPLE", L"Texture\\Btn_RedGiantBat.bmp");
		break;
	case TOOL_ID::BTN_GIANT_BAT:
		btnTex = ResourceMgr::GetInstance().Load<Texture>(L"GIANT_BAT_SAMPLE", L"Texture\\Btn_GiantBat.bmp");
		break;
	case TOOL_ID::BTN_GIANT_SKULL:
		btnTex = ResourceMgr::GetInstance().Load<Texture>(L"GIANT_SKULL_SAMPLE", L"Texture\\Btn_GiantSkull.bmp");
		break;
	case TOOL_ID::BTN_BANSHEE:
		btnTex = ResourceMgr::GetInstance().Load<Texture>(L"BANSHEE_SAMPLE", L"Texture\\Btn_Banshee.bmp");
		break;
	case TOOL_ID::BTN_ICE_GRAY_SKULL:
		btnTex = ResourceMgr::GetInstance().Load<Texture>(L"ICE_GRAY_SKULL_SAMPLE", L"Texture\\Btn_GrayIceSkull.bmp");
		break;
	case TOOL_ID::BTN_MINOTAUR:
		btnTex = ResourceMgr::GetInstance().Load<Texture>(L"MINOTAUR_SAMPLE", L"Texture\\Btn_Minotaur.bmp");
		break;
	case TOOL_ID::BTN_ICE_MAGE:
		btnTex = ResourceMgr::GetInstance().Load<Texture>(L"ICE_MAGE_SAMPLE", L"Texture\\Btn_IceMage.bmp");
		break;
	case TOOL_ID::BTN_OVIBOS:
		btnTex = ResourceMgr::GetInstance().Load<Texture>(L"OVIBOS_SAMPLE", L"Texture\\Btn_Ovibos.bmp");
		break;
	case TOOL_ID::BTN_DOOR_0DEG:
		btnTex = ResourceMgr::GetInstance().Load<Texture>(L"DOOR_0DEG_SAMPLE", L"Texture\\Btn_LockedDoor_0Deg.bmp");
		break;
	case TOOL_ID::BTN_DOOR_90DEG:
		btnTex = ResourceMgr::GetInstance().Load<Texture>(L"DOOR_90DEG_SAMPLE", L"Texture\\Btn_LockedDoor_90Deg.bmp");
		break;
	case TOOL_ID::BTN_DOOR_180DEG:
		btnTex = ResourceMgr::GetInstance().Load<Texture>(L"DOOR_0DEG_SAMPLE", L"Texture\\Btn_LockedDoor_0Deg.bmp");
		break;
	case TOOL_ID::BTN_DOOR_270DEG:
		btnTex = ResourceMgr::GetInstance().Load<Texture>(L"DOOR_270DEG_SAMPLE", L"Texture\\Btn_LockedDoor_270Deg.bmp");
		break;
	}

	
	if (nullptr != btnTex)
	{
		Vec2 mousePos = MOUSE_POS;
		Vec2 btnTexOrgSize = btnTex->GetSize();
		Vec2 btnTexSize = btnTexOrgSize * 2.f;

		AlphaBlend(
			BACK_BUF_DC,
			(int)(mousePos.x - btnTexSize.x / 2.f),
			(int)(mousePos.y - btnTexSize.y / 2.f),
			(int)btnTexSize.x,
			(int)btnTexSize.y,
			btnTex->GetDC(),
			0, 0,
			(int)btnTexOrgSize.x,
			(int)btnTexOrgSize.y,
			mBlendFunc
		);
	}
}

void ToolScene::Destory()
{
	Scene::Destroy();
}

void ToolScene::Enter()
{
	SetMenu(APP_INSTANCE.GetHwnd(), APP_INSTANCE.GetMainMenuHandle());
	APP_INSTANCE.SetWindowSize(true);
	TOOL_INSTANCE.EnableWindow();
	// 툴에 사용할 모든 타일을 벡터에 넣음
	// 넣고 나서 16열로 출력
	CameraMgr::GetInstance().RemoveEffect();
	CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::FADE_IN, 1.0f);
	CameraMgr::GetInstance().SetLookPos(Vec2(TILE_SIZE * 15, GROUND_STANDARD));
	Vec2 texSize = mDefaultTexture->GetSize();

	ToolUI* toolUI = new ToolUI;
	toolUI->SetTexture(mDefaultTexture);
	toolUI->SetPos(Vec2(0, WINDOW_HEIGHT_SIZE - (TILE_SIZE * 3)));

	// 맵 이미지 내의 인덱스
	int colMax = WINDOW_WIDTH_SIZE / TILE_SIZE;
	int rowMax = WINDOW_HEIGHT_SIZE / TILE_SIZE;

	// 실제로 화면에 그려질 인덱스
	int col = 0;
	int row = 0;

	for (int y = 0; y < texSize.y / IMAGE_TILE_SIZE_Y; ++y)
	{
		for (int x = 0; x < (texSize.x / IMAGE_TILE_SIZE_X - 1); ++x)
		{
			IconUI* child = new IconUI;
			child->SetLTPos(Vec2(x * IMAGE_TILE_SIZE_X, y * IMAGE_TILE_SIZE_Y));
			child->SetPos(Vec2(col * TILE_SIZE, row * TILE_SIZE));
			child->SetParentUI(toolUI);

			toolUI->AddChild(child);

			if (col < colMax - 1)
				col++;

			else
			{
				col = 0;
				row++;
			}
		}
	}

	Texture* checkBtnTex = ResourceMgr::GetInstance().Load<Texture>(L"checkBtn", L"Texture\\CheckButton.bmp");
	Vec2 checkTexSize = checkBtnTex->GetSize();
	CheckButtonUI* pressedCheckBtnUI = new CheckButtonUI;
	pressedCheckBtnUI->SetTexture(checkBtnTex);
	pressedCheckBtnUI->SetPos(Vec2(30, 30));
	pressedCheckBtnUI->SetSize(checkTexSize);
	pressedCheckBtnUI->SetIndex(true);
	pressedCheckBtnUI->TextureProcessing(
		Vec2(0, 0),
		Vec2(checkTexSize.x / 2.f, 0.f),
		Vec2(checkTexSize.x / 2.f, checkTexSize.y));

	CheckButtonUI* singlyCheckBtnUI = new CheckButtonUI;
	singlyCheckBtnUI->SetTexture(checkBtnTex);
	singlyCheckBtnUI->SetPos(Vec2(30, 70));
	singlyCheckBtnUI->SetSize(checkTexSize);
	singlyCheckBtnUI->SetIndex(false);
	singlyCheckBtnUI->TextureProcessing(
		Vec2(0, 0),
		Vec2(checkTexSize.x / 2.f, 0.f),
		Vec2(checkTexSize.x / 2.f, checkTexSize.y));

	CheckButtonUI::SetCheckedButton(pressedCheckBtnUI);



	AddGameObject(pressedCheckBtnUI, pressedCheckBtnUI->GetType());
	AddGameObject(singlyCheckBtnUI, singlyCheckBtnUI->GetType());
	AddGameObject(toolUI, toolUI->GetType());

}

void ToolScene::Exit()
{
	TOOL_INSTANCE.DisableWindow();
	SetMenu(APP_INSTANCE.GetHwnd(), NULL);
	APP_INSTANCE.SetWindowSize(false);
	DeleteObjGroup(OBJECT_TYPE::UI);
	CleanObjectGroup(OBJECT_TYPE::WALL);
	CleanObjectGroup(OBJECT_TYPE::FOOTHOLD);
	DeleteObjGroup(OBJECT_TYPE::TILE);
	DeleteObjGroup(OBJECT_TYPE::TILE_BG);
	DeleteObjGroup(OBJECT_TYPE::EVENT_OBJECT);
	CleanObjectGroup(OBJECT_TYPE::MONSTER_EFFECT);
	DeleteObjGroup(OBJECT_TYPE::MONSTER);
	DeleteObjGroup(OBJECT_TYPE::DUNGEON_OBJECT);
}

void ToolScene::RemoveTile(Vec2 _pos)
{
	// 누른 녀석의 컴포넌트 상태에 따라 처리
	OBJECT_TYPE tileType = mCheckedObjectType;

	const std::vector<GameObject*>& tileGroup = GetObjectGroup(tileType);


	for (int i = 0; i < tileGroup.size(); ++i)
	{
		if (tileGroup[i]->GetPos() == _pos + TILE_OFFSET)
		{
			Tile* tile = static_cast<Tile*>(tileGroup[i]);
			CollisionComponent* colCom = tile->GetCollisionComponent();
			if (nullptr != colCom)
			{
				EventRegisteror::GetInstance().DeleteObjectFromScene(colCom);
			}
			EventRegisteror::GetInstance().DeleteObject(tile);
			break;
		}
	}
}

//IconUI* ToolScene::CutTile(UI* _parentUI, Vec2 _ltPos, Vec2 _slice)
//{
//	size_t size = _parentUI->GetChildUI().size();
//	int row = (int)(size / (WINDOW_WIDTH_SIZE / TILE_SIZE));
//	int col = size % (WINDOW_WIDTH_SIZE / TILE_SIZE);
//
//
//	IconUI* iconUI = new IconUI;
//	iconUI->SetLTPos(_ltPos);
//	iconUI->SetPos(Vec2(col * TILE_SIZE, row * TILE_SIZE));
//	iconUI->SetParentUI(_parentUI);
//
//	return iconUI;
//}
//
//void ToolScene::CutTiles(UI* _parentUI, Vec2 _ltPos, Vec2 _offset, Vec2 _slice, int _tileCount)
//{
//	for (int i = 0; i < _tileCount; ++i)
//	{
//		_parentUI->AddChild(CutTile(_parentUI, _ltPos + (_offset * (float)i), _slice));
//	}
//}

void ToolScene::SetupTile()
{
	// 여기서 타입에 따라 갈려야 하나?

	IconUI* selectedUI = IconUI::GetSelectedUI();
	Vec2 mousePos = WORLD_POS(MOUSE_POS);
	Vec2 tilePos = CameraMgr::GetInstance().GetTileCoord(mousePos);

	OBJECT_TYPE tileObjType = mCheckedObjectType;

	const std::vector<GameObject*>& tileGroup = GetObjectGroup(tileObjType);
	Tile* tile = nullptr;

	// 해당 위치에 타일이 있는지 검사
	for (int i = 0; i < tileGroup.size(); ++i)
	{
		if (tileGroup[i]->GetPos() == tilePos + TILE_OFFSET)
		{
			tile = static_cast<Tile*>(tileGroup[i]);
			break;
		}
	}

	if (nullptr == tile)
	{
		// 타일이 없는 자리의 경우

		if (nullptr != selectedUI)
		{
			tile = new Tile;
			tile->SetPos(tilePos + Vec2(TILE_SIZE / 2.f, TILE_SIZE / 2.f));
			tile->SetLTPos(selectedUI->GetLTPos());

			TILE_TYPE tileType = mCheckedTileType;
			switch (tileType)
			{
			case TILE_TYPE::WALL:
			{
				tile->CreateWall();
				tile->SetTileType(tileType);
				EventRegisteror::GetInstance().CreateObject(tile, OBJECT_TYPE::TILE);
				EventRegisteror::GetInstance().CreateObject(tile->GetCollisionComponent(), tile->GetCollisionComponent()->GetType());
			}
			break;
			case TILE_TYPE::FOOTHOLD:
			{
				tile->CreateFoothold();
				tile->SetTileType(tileType);
				EventRegisteror::GetInstance().CreateObject(tile, OBJECT_TYPE::TILE);
				EventRegisteror::GetInstance().CreateObject(tile->GetCollisionComponent(), tile->GetCollisionComponent()->GetType());
			}
			break;
			case TILE_TYPE::NONE:
				tile->SetTileType(tileType);
				tile->SetType(OBJECT_TYPE::TILE_BG);
				EventRegisteror::GetInstance().CreateObject(tile, OBJECT_TYPE::TILE_BG);
				break;
			}


		}

	}

	else
	{
		// LT Pos가 기존에 있는 것과 내가 선택한게 같다면 Return
		if (nullptr != selectedUI)
		{
			if (selectedUI->GetLTPos() == tile->GetLTPos())
				return;
		}

		// 타일이 있는 자리의 경우

		// 타일이 가진 컴포넌트가 있다면
		CollisionComponent* tileComponent = tile->GetCollisionComponent();

		if (nullptr != tileComponent)
		{
			// 내 위치와 같은 Wall과 Foothold를 지워줘야 한다

			OBJECT_TYPE type = tileComponent->GetType();


			if (OBJECT_TYPE::FOOTHOLD == type && TILE_TYPE::FOOTHOLD == mCheckedTileType ||
				nullptr != selectedUI && TILE_TYPE::FOOTHOLD == mCheckedTileType)
			{
				static_cast<LineCollider*>(tile->GetCollisionComponent()->GetCollider())->SetNextLineType();
				return;
			}

			if (OBJECT_TYPE::FOOTHOLD == type ||
				OBJECT_TYPE::WALL == type)
			{
				//해당 타입에 대한 오브젝트 그룹을 가져옴
				std::vector<GameObject*>& objects = mObjects[(UINT)type];

				std::vector<GameObject*>::iterator iter = objects.begin();

				for (; iter != objects.end(); ++iter)
				{
					Vec2 tilePos = tile->GetPos();
					Vec2 objPos = iter.operator*()->GetPos();

					// 위치가 같은 게 있다면
					if (tilePos == objPos)
					{
						//삭제하고 씬에서 제거
						delete* iter;
						objects.erase(iter);
						break;
					}
				}

			}

			tile->ClearCollisionComponent();
		}

		if (OBJECT_TYPE::TILE == tileObjType)
		{
			switch (mCheckedTileType)
			{
			case TILE_TYPE::WALL:
				tile->CreateWall();
				EventRegisteror::GetInstance().CreateObject(tile->GetCollisionComponent(), tile->GetCollisionComponent()->GetType());
				break;
			case TILE_TYPE::FOOTHOLD:
				tile->CreateFoothold();
				EventRegisteror::GetInstance().CreateObject(tile->GetCollisionComponent(), tile->GetCollisionComponent()->GetType());
				break;
			case TILE_TYPE::NONE:
				break;
			}

			tile->SetTileType(mCheckedTileType);
		}

	}
}

void ToolScene::AuxLineRender()
{
	// 가로줄
	for (int i = 0; i < ASSISTANT_LINE_Y; i += TILE_SIZE)
	{
		Vec2 renderPos(0, i);
		renderPos = RENDER_POS(renderPos);
		MoveToEx(BACK_BUF_DC, (int)renderPos.x, (int)renderPos.y, nullptr);
		LineTo(BACK_BUF_DC, (int)(renderPos.x + ASSISTANT_LINE_X), (int)renderPos.y);
	}

	// 세로줄
	for (int i = 0; i < ASSISTANT_LINE_X; i += TILE_SIZE)
	{
		Vec2 renderPos(i, 0);
		renderPos = RENDER_POS(renderPos);
		MoveToEx(BACK_BUF_DC, (int)renderPos.x, (int)renderPos.y, nullptr);
		LineTo(BACK_BUF_DC, (int)renderPos.x, (int)(renderPos.y + ASSISTANT_LINE_Y));
	}
}

void ToolScene::GuideCircle()
{
	Vec2 renderPos(-20, TILE_SIZE * 24 + (TILE_SIZE / 2));
	renderPos = RENDER_POS(renderPos);


	Brush magentaBrush(
		BACK_BUF_DC,
		BRUSH_TYPE::MAGENTA
	);

	Ellipse(
		BACK_BUF_DC,
		(int)(renderPos.x - 15),
		(int)(renderPos.y - 15),
		(int)(renderPos.x + 15),
		(int)(renderPos.y + 15)
	);
}

void ToolScene::GuideText()
{
	static wchar_t pressedType[COMMENT_MAX_SIZE] = L"> 하나씩 출력";
	static wchar_t singlyType[COMMENT_MAX_SIZE] = L"> 연속 출력";
	TextOut(BACK_BUF_DC, 60, 20, pressedType, (int)wcslen(pressedType));
	TextOut(BACK_BUF_DC, 60, 60, singlyType, (int)wcslen(singlyType));

	SetTextColor(BACK_BUF_DC, RGB(0, 64, 128));
	static wchar_t nextPage[COMMENT_MAX_SIZE] = L"> 다음 타일 페이지       (Page     Up)";
	static wchar_t prevPage[COMMENT_MAX_SIZE] = L"> 이전 타일 페이지       (Page Down)";
	static wchar_t comment[COMMENT_MAX_SIZE] = L"> 선택 해제 & 타일 지우기 (우클릭)";
	static wchar_t saveComment[COMMENT_MAX_SIZE] = L"> 맵 저장하기                (CTRL  +  S)";
	static wchar_t loadComment[COMMENT_MAX_SIZE] = L"> 맵 불러오기                (CTRL  +  O)";

	TextOut(BACK_BUF_DC, WINDOW_WIDTH_SIZE - 270, WINDOW_HEIGHT_SIZE - TILE_SIZE * 3 - 100, saveComment, (int)wcslen(saveComment));
	TextOut(BACK_BUF_DC, WINDOW_WIDTH_SIZE - 270, WINDOW_HEIGHT_SIZE - TILE_SIZE * 3 - 80, loadComment, (int)wcslen(loadComment));
	TextOut(BACK_BUF_DC, WINDOW_WIDTH_SIZE - 270, WINDOW_HEIGHT_SIZE - TILE_SIZE * 3 - 60, nextPage, (int)wcslen(nextPage));
	TextOut(BACK_BUF_DC, WINDOW_WIDTH_SIZE - 270, WINDOW_HEIGHT_SIZE - TILE_SIZE * 3 - 40, prevPage, (int)wcslen(prevPage));
	TextOut(BACK_BUF_DC, WINDOW_WIDTH_SIZE - 270, WINDOW_HEIGHT_SIZE - TILE_SIZE * 3 - 20, comment, (int)wcslen(comment));

	static wchar_t tilePage[COMMENT_MAX_SIZE] = L"> 타일 선택 UI";
	TextOut(BACK_BUF_DC, 0, WINDOW_HEIGHT_SIZE - TILE_SIZE * 3 - 20, tilePage, (int)wcslen(tilePage));
}

bool ToolScene::IsTileableArea(Vec2 _tilePos)
{
	Vec2 mousePos = WORLD_POS(MOUSE_POS);
	Vec2 tilePos = CameraMgr::GetInstance().GetTileCoord(mousePos);

	return (tilePos.y >= 0.f && tilePos.x >= 0.f) 
		&& (MOUSE_POS.y < WINDOW_HEIGHT_SIZE - (TILE_SIZE * 3)) 
		&& (MOUSE_POS.x < WINDOW_WIDTH_SIZE)
		&& (MOUSE_POS.x > 50.f && MOUSE_POS.y > 50.f);
}

void ToolScene::Save()
{
	if (GetSaveFileName(&mOFN))
	{
		std::wstring fileName = GetFileName();

		if (L".map" != fileName.substr(fileName.size() - 4))
		{
			fileName += L".map";
		}

		FILE* fp = nullptr;
		_wfopen_s(&fp, fileName.c_str(), L"wb");

		std::vector<GameObject*>& tileGroup = mObjects[(UINT)OBJECT_TYPE::TILE];
		std::vector<GameObject*>& bgTileGroup = mObjects[(UINT)OBJECT_TYPE::TILE_BG];
		std::vector<GameObject*>& monsterGroup = mObjects[(UINT)OBJECT_TYPE::MONSTER];
		std::vector<GameObject*>& dungeonObjGroup = mObjects[(UINT)OBJECT_TYPE::DUNGEON_OBJECT];

		std::vector<GameObject*> tileTotalGroup;
		tileTotalGroup.reserve(tileGroup.size() + bgTileGroup.size());
		tileTotalGroup.insert(tileTotalGroup.end(), tileGroup.begin(), tileGroup.end());
		tileTotalGroup.insert(tileTotalGroup.end(), bgTileGroup.begin(), bgTileGroup.end());
		
		size_t tileSize = tileTotalGroup.size();
		size_t monsterSize = monsterGroup.size();
		size_t dungeonObjSize = dungeonObjGroup.size();

		fwrite(&tileSize, sizeof(size_t), 1, fp);
		for (const auto& tile : tileTotalGroup)
		{
			static_cast<Tile*>(tile)->Save(fp);
		}
		fwrite(&monsterSize, sizeof(size_t), 1, fp);
		for (int i = 0; i < monsterSize; ++i)
		{
			monsterGroup[i]->Save(fp);
		}

		fwrite(&dungeonObjSize, sizeof(size_t), 1, fp);
		for (int i = 0; i < dungeonObjSize; ++i)
		{
			dungeonObjGroup[i]->Save(fp);
		}
		fclose(fp);
	}
}

void ToolScene::Load()
{
	if (GetOpenFileName(&mOFN))
	{
		_wchdir(APP_INSTANCE.GetBaseAddress().c_str());
		std::wstring fileName = GetFileName();

		FILE* fp = nullptr;
		errno_t err = _wfopen_s(&fp, fileName.c_str(), L"rb");

		if (0 != err)
		{
			assert(nullptr);
		}

		DeleteObjGroup(OBJECT_TYPE::TILE);
		CleanObjectGroup(OBJECT_TYPE::MONSTER_EFFECT);
		DeleteObjGroup(OBJECT_TYPE::MONSTER);
		DeleteObjGroup(OBJECT_TYPE::DUNGEON_OBJECT);

		size_t tileSize = 0;

		fread(&tileSize, sizeof(size_t), 1, fp);
		TileInitialize(tileSize);

		std::vector<GameObject*>& tileGroup = mObjects[(UINT)OBJECT_TYPE::TILE];
		for (const auto& tile : tileGroup)
		{
			static_cast<Tile*>(tile)->Load(fp);
		}

		auto iter = tileGroup.begin();
		for (; iter != tileGroup.end(); )
		{
			Tile* tile = static_cast<Tile*>(*iter);
			if (TILE_TYPE::NONE == tile->GetTileType())
			{
				tile->SetType(OBJECT_TYPE::TILE_BG);
				mObjects[(UINT)OBJECT_TYPE::TILE_BG].push_back(std::move(*iter));
				iter = tileGroup.erase(iter);
			}

			else
			{
				iter++;
			}
		}
		size_t monsterSize = 0;
		fread(&monsterSize, sizeof(size_t), 1, fp);

		for (int i = 0; i < monsterSize; ++i)
		{
			Vec2 monsterPos = {};
			TOOL_ID id = {};
			
			fread(&monsterPos, sizeof(Vec2), 1, fp);
			fread(&id, sizeof(TOOL_ID), 1, fp);

			SetupMonster(id, monsterPos);
		}

		size_t dungeonObjSize = 0;
		fread(&dungeonObjSize, sizeof(size_t), 1, fp);
		for (int i = 0; i < dungeonObjSize; ++i)
		{
			Vec2 dungeonObjPos = {};
			TOOL_ID id = {};

			fread(&dungeonObjPos, sizeof(Vec2), 1, fp);
			fread(&id, sizeof(TOOL_ID), 1, fp);

			SetupDungeonObject(id, dungeonObjPos);
		}

		err = fclose(fp);
	}

	
}




