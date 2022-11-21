#include "pch.h"
#include "ToolUI.h"
#include "Tile.h"
#include "Texture.h"
#include "KeyMgr.h"

ToolUI::ToolUI()
	: UI(false)
{
	SetState();
	SetType(OBJECT_TYPE::UI);
}

ToolUI::~ToolUI()
{
}

void ToolUI::Initialize()
{
}

void ToolUI::Update()
{
	if (!GetState())
		return;

	if (GetTexture())
	{
		if (IS_JUST_PRESSED(KEY::PAGE_UP) && mCurPage > 0)
			mCurPage--;
		

		if (IS_JUST_PRESSED(KEY::PAGE_DOWN))
			mCurPage++;
	}

	UI::Update();
}

void ToolUI::Render()
{
	if (!GetState())
		return;

	Texture* texture = GetTexture();
	if (nullptr != texture)
	{
		Rectangle(BACK_BUF_DC,
			0,
			WINDOW_HEIGHT_SIZE - (TILE_SIZE * 3),
			WINDOW_WIDTH_SIZE,
			WINDOW_HEIGHT_SIZE);
	}

	UI::Render();
}

void ToolUI::Destroy() 
{
}

bool ToolUI::OnMouse()
{
	const std::vector<UI*>& iconUI = GetChildUI();
	for (int i = 0; i < iconUI.size(); ++i)
	{
		if (iconUI[i]->OnMouse())
			iconUI[i]->SetOnMouseState(true);
		else
			iconUI[i]->SetOnMouseState(false);
	}

	return false;
}

bool ToolUI::OnClicked()
{
	const std::vector<UI*>& iconUI = GetChildUI();
	for (int i = 0; i < iconUI.size(); ++i)
	{
		if (iconUI[i]->OnClicked())
			iconUI[i]->SetOnClickedState(true);
		else
			iconUI[i]->SetOnClickedState(false);
	}

	return false;
}

