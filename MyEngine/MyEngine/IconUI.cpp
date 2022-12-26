#include "pch.h"
#include "IconUI.h"
#include "Texture.h"
#include "CameraMgr.h"
#include "MouseMgr.h"
#include "CheckButtonUI.h"
#include "ToolUI.h"
#include "ToolWindows.h"

IconUI* IconUI::selectedUI = nullptr;
IconUI::IconUI()
	: UI(false)
{
	SetState();
}

IconUI::~IconUI()
{
}

void IconUI::Initialize()
{
}

void IconUI::Update()
{
	if (IS_RBUTTON_CLICKED)
		selectedUI = nullptr;

	if (!GetState())
		return;

	ToolUI* parentUI = static_cast<ToolUI*>(GetParentUI());

	Vec2 parentPos = parentUI->GetPos();
	Vec2 pos = parentPos + GetPos();

	Vec2 IconPos = CameraMgr::GetInstance().GetIconUIPos(pos, parentUI->GetPage());
	if (IconPos.y < WINDOW_HEIGHT_SIZE - (TILE_SIZE * 3))
		return;

	if (mOnMouse)
	{
		if (mOnClicked)
		{
			TOOL_INSTANCE.AllButtonRelease();
			selectedUI = this;
		}
	}


	
}

void IconUI::Render()
{	
	if (!GetState())
		return;

	ToolUI* parentUI = (ToolUI*)GetParentUI();

	if (nullptr != parentUI)
	{
		Texture* texture = parentUI->GetTexture();
		
		if (nullptr != texture)
		{
			Vec2 pos = parentUI->GetPos();
			pos += GetPos();
			pos = CameraMgr::GetInstance().GetIconUIPos(pos, parentUI->GetPage());
			if (pos.y < WINDOW_HEIGHT_SIZE - (TILE_SIZE * 3))
				return;

			TransparentBlt(
				BACK_BUF_DC,
				(int)(pos.x),
				(int)(pos.y),
				TILE_SIZE,
				TILE_SIZE,
				texture->GetDC(),
				(int)(mLT.x),
				(int)(mLT.y),
				IMAGE_TILE_SIZE_X,
				IMAGE_TILE_SIZE_Y,
				RGB(255, 0, 255)
			);

			if (this == selectedUI)
			{
				Brush brush(BACK_BUF_DC, BRUSH_TYPE::HOLLOW);
				Pen pen(BACK_BUF_DC, PEN_TYPE::RED);

				Rectangle(BACK_BUF_DC,
					(int)pos.x,
					(int)pos.y,
					(int)(pos.x + TILE_SIZE),
					(int)(pos.y + TILE_SIZE));
			}
					
		}
	}
}

void IconUI::Destroy()
{
}

bool IconUI::OnMouse()
{
	ToolUI* parentUI = static_cast<ToolUI*>(GetParentUI());
	Vec2 mousePos = MOUSE_POS;

	Vec2 parentPos = parentUI->GetPos();
	Vec2 pos = parentPos + GetPos();

	pos = CameraMgr::GetInstance().GetIconUIPos(pos, parentUI->GetPage());

	return (pos.x <= mousePos.x && pos.x + TILE_SIZE >= mousePos.x &&
		pos.y <= mousePos.y && pos.y + TILE_SIZE >= mousePos.y);
}

bool IconUI::OnClicked()
{
	return OnMouse() && IS_LBUTTON_CLICKED;
}
