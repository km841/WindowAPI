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
	IconUI* selectedUI = IconUI::GetSelectedUI();
	Vec2 mousePos = WORLD_POS(MOUSE_POS);
	Vec2 tilePos = CameraMgr::GetInstance().GetTileCoord(mousePos);

	if (nullptr != selectedUI)
	{
		if (IS_LBUTTON_CLICKED && (MOUSE_POS.y < WINDOW_HEIGHT_SIZE - (TILE_SIZE * 3)))
		{
			const std::vector<GameObject*>& tileGroup = GetObjectGroup(OBJECT_TYPE::TILE);
			Tile* tile = nullptr;
			for (int i = 0; i < tileGroup.size(); ++i)
			{
				if (tileGroup[i]->GetPos() == tilePos)
				{
					tile = dynamic_cast<Tile*>(tileGroup[i]);
				}
			}

			if (nullptr == tile)
			{
				Tile* tile = new Tile;
				tile->SetPos(tilePos);
				tile->SetLTPos(selectedUI->GetLTPos());

				TILE_TYPE tileType = (TILE_TYPE)(CheckButtonUI::GetCheckButtonUI()->GetIndex());
				tile->SetTileType(tileType);

				switch (tileType)
				{
				case TILE_TYPE::WALL:
					tile->CreateWall();
					break;
				case TILE_TYPE::FOOTHOLD:
					tile->CreateFoothold();
					break;
				case TILE_TYPE::NONE:
					
					break;
				}

				EventRegisteror::GetInstance().CreateObject(tile, OBJECT_TYPE::TILE);

			}

			else
			{
				TILE_TYPE tileType = (TILE_TYPE)(CheckButtonUI::GetCheckButtonUI()->GetIndex());
				CollisionComponent* tileComponent = tile->GetCollisionComponent();

				if (nullptr != tileComponent)
				{
					tile->ClearCollisionComponent();
					delete tileComponent;
				}

				switch (tileType)
				{
				case TILE_TYPE::WALL:
					tile->CreateWall();
					break;
				case TILE_TYPE::FOOTHOLD:
					tile->CreateFoothold();
					break;
				case TILE_TYPE::NONE:
					break;
				}

				tile->SetTileType(tileType);
			}
		}
	}
	else
	{
		if (IS_RBUTTON_CLICKED)
			RemoveTile(tilePos);
	}

	if (IS_PRESSED(KEY::LCTRL) && IS_JUST_PRESSED(KEY::S))
	{
		Save();
	}

	if (IS_PRESSED(KEY::LCTRL) && IS_JUST_PRESSED(KEY::O))
	{
		Load();
	}


	Scene::Update();
}

void ToolScene::Render()
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
	

	Scene::Render();
	
	SetTextColor(BACK_BUF_DC, RGB(0, 0, 0));
	static wchar_t collisionPage[COMMENT_MAX_SIZE] = L"> 충돌체 타입 선택 UI";
	TextOut(BACK_BUF_DC, 2, 10, collisionPage, (int)wcslen(collisionPage));

	SetTextColor(BACK_BUF_DC, RGB(128, 64, 0));
	static wchar_t tileColType_Wall[COMMENT_MAX_SIZE] = L" 타일 충돌 타입: 벽";
	static wchar_t tileColType_Foothold[COMMENT_MAX_SIZE] = L" 타일 충돌 타입: 발판";
	static wchar_t tileColType_None[COMMENT_MAX_SIZE] = L" 타일 충돌 타입: 없음";

	TextOut(BACK_BUF_DC, 50, 40, tileColType_Wall, (int)wcslen(tileColType_Wall));
	TextOut(BACK_BUF_DC, 50, 80, tileColType_Foothold, (int)wcslen(tileColType_Foothold));
	TextOut(BACK_BUF_DC, 50, 120, tileColType_None, (int)wcslen(tileColType_None));

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


	
}

void ToolScene::Enter()
{
	// 툴에 사용할 모든 타일을 벡터에 넣음
	// 넣고 나서 16열로 출력
	CameraMgr::GetInstance().RemoveEffect();
	CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::FADE_IN, 1.0f);
	CameraMgr::GetInstance().SetLookPos(Vec2(TILE_SIZE * 15, TILE_SIZE * 20));
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
	CheckButtonUI* wallCheckBtnUI = new CheckButtonUI;
	wallCheckBtnUI->SetTexture(checkBtnTex);
	wallCheckBtnUI->SetSize(checkBtnTex->GetSize());
	wallCheckBtnUI->SetPos(Vec2(20, 50));
	wallCheckBtnUI->TextureProcessing(
		Vec2(0.f, 0.f),
		Vec2(checkBtnTex->GetWidth() / 2.f, 0.f),
		Vec2(checkBtnTex->GetWidth() / 2.f, (float)checkBtnTex->GetHeight()));
	wallCheckBtnUI->SetIndex((int)TILE_TYPE::WALL);

	CheckButtonUI* footHoldCheckBtnUI = new CheckButtonUI;
	footHoldCheckBtnUI->SetTexture(checkBtnTex);
	footHoldCheckBtnUI->SetSize(checkBtnTex->GetSize());
	footHoldCheckBtnUI->SetPos(Vec2(20, 90));
	footHoldCheckBtnUI->TextureProcessing(
		Vec2(0.f, 0.f),
		Vec2(checkBtnTex->GetWidth() / 2.f, 0.f),
		Vec2(checkBtnTex->GetWidth() / 2.f, (float)checkBtnTex->GetHeight()));
	footHoldCheckBtnUI->SetIndex((int)TILE_TYPE::FOOTHOLD);

	CheckButtonUI* noneCheckBtnUI = new CheckButtonUI;
	noneCheckBtnUI->SetTexture(checkBtnTex);
	noneCheckBtnUI->SetSize(checkBtnTex->GetSize());
	noneCheckBtnUI->SetPos(Vec2(20, 130));
	noneCheckBtnUI->TextureProcessing(
		Vec2(0.f, 0.f),
		Vec2(checkBtnTex->GetWidth() / 2.f, 0.f),
		Vec2(checkBtnTex->GetWidth() / 2.f, (float)checkBtnTex->GetHeight()));
	noneCheckBtnUI->SetIndex((int)TILE_TYPE::NONE);

	CheckButtonUI::SetCheckButtonUI(noneCheckBtnUI);


	EventRegisteror::GetInstance().CreateObject(toolUI, toolUI->GetType());
	EventRegisteror::GetInstance().CreateObject(wallCheckBtnUI, wallCheckBtnUI->GetType());
	EventRegisteror::GetInstance().CreateObject(footHoldCheckBtnUI, footHoldCheckBtnUI->GetType());
	EventRegisteror::GetInstance().CreateObject(noneCheckBtnUI, noneCheckBtnUI->GetType());
}

void ToolScene::Exit()
{
	DeleteObjGroup(OBJECT_TYPE::UI);
	DeleteObjGroup(OBJECT_TYPE::TILE);
}

void ToolScene::RemoveTile(Vec2 _pos)
{
	const std::vector<GameObject*>& tileGroup = GetObjectGroup(OBJECT_TYPE::TILE);
	for (int i = 0; i < tileGroup.size(); ++i)
	{
		if (tileGroup[i]->GetPos() == _pos)
		{
			EventRegisteror::GetInstance().DeleteObject(tileGroup[i]);
			break;
		}
	}
}

IconUI* ToolScene::CutTile(UI* _parentUI, Vec2 _ltPos, Vec2 _slice)
{
	size_t size = _parentUI->GetChildUI().size();
	int row = (int)(size / (WINDOW_WIDTH_SIZE / TILE_SIZE));
	int col = size % (WINDOW_WIDTH_SIZE / TILE_SIZE);


	IconUI* iconUI = new IconUI;
	iconUI->SetLTPos(_ltPos);
	iconUI->SetPos(Vec2(col * TILE_SIZE, row * TILE_SIZE));
	iconUI->SetParentUI(_parentUI);

	return iconUI;
}

void ToolScene::CutTiles(UI* _parentUI, Vec2 _ltPos, Vec2 _offset, Vec2 _slice, int _tileCount)
{
	for (int i = 0; i < _tileCount; ++i)
	{
		_parentUI->AddChild(CutTile(_parentUI, _ltPos + (_offset * (float)i), _slice));
	}
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
		_wfopen_s(&fp, fileName.c_str(), L"w");

		const std::vector<GameObject*>& tileGroup = GetObjectGroup(OBJECT_TYPE::TILE);
		size_t tileSize = tileGroup.size();
		fwrite(&tileSize, sizeof(int), 1, fp);

		
		for (const auto& tile : tileGroup)
		{
			dynamic_cast<Tile*>(tile)->Save(fp);
		}

		fclose(fp);
	}
}

void ToolScene::Load()
{
	if (GetOpenFileName(&mOFN))
	{
		std::wstring fileName = GetFileName();
		

		FILE* fp = nullptr;
		_wfopen_s(&fp, fileName.c_str(), L"r");

		
		DeleteObjGroup(OBJECT_TYPE::TILE);

		int tileSize = 0;
		fread(&tileSize, sizeof(int), 1, fp);
		TileInitialize(tileSize);

		const std::vector<GameObject*>& tileGroup = GetObjectGroup(OBJECT_TYPE::TILE);
		for (const auto& tile : tileGroup)
		{
			dynamic_cast<Tile*>(tile)->Load(fp);
		}

		fclose(fp);
	}
}




