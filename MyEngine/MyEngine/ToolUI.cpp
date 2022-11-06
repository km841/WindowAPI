#include "pch.h"
#include "ToolUI.h"
#include "Tile.h"
#include "Texture.h"

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

	}

	UI::Update();
}

void ToolUI::Render()
{
	Texture* texture = GetTexture();
	if (texture)
	{
		Rectangle(BACK_BUF_DC,
			0,
			WINDOW_HEIGHT_SIZE - (TILE_SIZE * 2) - HEIGHT_CORRECT,
			WINDOW_WIDTH_SIZE,
			WINDOW_HEIGHT_SIZE);
	}

	UI::Render();
}

void ToolUI::Destroy()
{
}
