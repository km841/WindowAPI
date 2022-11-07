#include "pch.h"
#include "ToolUI.h"
#include "Tile.h"
#include "Texture.h"
#include "KeyMgr.h"

ToolUI::ToolUI()
	: UI(false)
{
}

ToolUI::~ToolUI()
{
}

void ToolUI::Initialize()
{
}

void ToolUI::Update()
{
	if (GetTexture())
	{
		if (IS_JUST_PRESSED(KEY::PAGE_UP) && mCurPage > 0)
		{
			mCurPage--;
		}

		if (IS_JUST_PRESSED(KEY::PAGE_DOWN))
		{
			mCurPage++;
		}
	}

	UI::Update();
}

void ToolUI::Render()
{
	Texture* texture = GetTexture();
	if (nullptr != texture)
	{
		Rectangle(BACK_BUF_DC,
			0,
			WINDOW_HEIGHT_SIZE - (TILE_SIZE * 3) - HEIGHT_CORRECT,
			WINDOW_WIDTH_SIZE,
			WINDOW_HEIGHT_SIZE);
	}

	UI::Render();
}

void ToolUI::Destroy()
{
}

