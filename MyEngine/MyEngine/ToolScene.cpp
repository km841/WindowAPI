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

void ToolScene::Initialize()
{
	mDefaultTexture = ResourceMgr::GetInstance().Load<Texture>(L"TileMap", L"Texture\\Map.bmp");
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
		if (MOUSE_POS.y < WINDOW_HEIGHT_SIZE - (TILE_SIZE * 2) && IS_LBUTTON_CLICKED)
		{
			const std::vector<GameObject*>& tileGroup = GetObjectGroup(OBJECT_TYPE::TILE);
			bool existFlag = false;
			for (int i = 0; i < tileGroup.size(); ++i)
			{
				if (tileGroup[i]->GetPos() == tilePos)
					existFlag = true;
			}

			if (!existFlag)
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
		{
			RemoveTile(tilePos);
		}
	}


	Scene::Update();
}

void ToolScene::Render()
{

	Scene::Render();


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
			TILE_SIZE,
			TILE_SIZE,
			mBlendFunc
		);
	}


	
}

void ToolScene::Enter()
{
	// 툴에 사용할 모든 타일을 벡터에 넣음
	// 넣고 나서 16열로 출력
	CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::FADE_IN, 1.0f);
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

	// 툴 UI 작업
	for (int y = 0; y < texSize.y / TILE_SIZE; ++y)
	{
		for (int x = 0; x < (texSize.x / TILE_SIZE - 1); ++x)
		{
			IconUI* child = new IconUI;
			child->SetLTPos(Vec2(x * TILE_SIZE, y * TILE_SIZE));
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




