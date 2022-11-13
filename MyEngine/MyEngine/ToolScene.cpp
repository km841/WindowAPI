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

void ToolScene::Initialize()
{
	mDefaultTexture = ResourceMgr::GetInstance().Load<Texture>(L"TileMap", L"Texture\\Map2.bmp");
	assert(mDefaultTexture);

	mBlendFunc = {};
	mBlendFunc.BlendFlags = 0;
	mBlendFunc.AlphaFormat = AC_SRC_ALPHA;
	mBlendFunc.BlendOp = AC_SRC_OVER;
	mBlendFunc.SourceConstantAlpha = 127;
}

void ToolScene::Update()
{
	IconUI* selectedUI = IconUI::GetSelectedUI();
	Vec2 mousePos = WORLD_POS(MOUSE_POS);
	Vec2 tilePos = CameraMgr::GetInstance().GetTileCoord(mousePos);

	if (nullptr != selectedUI)
	{
		if (IS_LBUTTON_CLICKED && (MOUSE_POS.y < WINDOW_HEIGHT_SIZE - HEIGHT_CORRECT - (TILE_SIZE * 3)))
		{
			const std::vector<GameObject*>& tileGroup = GetObjectGroup(OBJECT_TYPE::TILE);
			bool existFlag = false;
			for (int i = 0; i < tileGroup.size(); ++i)
			{
				if (tileGroup[i]->GetPos() == tilePos)
					existFlag = true;
			}

			if (false == existFlag)
			{
				Tile* tile = new Tile;
				tile->SetPos(tilePos);
				tile->SetLTPos(selectedUI->GetLTPos());
				EventRegisteror::GetInstance().CreateObject(tile, OBJECT_TYPE::TILE);
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
	toolUI->SetPos(Vec2(0, WINDOW_HEIGHT_SIZE - (TILE_SIZE * 3) - HEIGHT_CORRECT));

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

	EventRegisteror::GetInstance().CreateObject(toolUI, OBJECT_TYPE::UI);
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




