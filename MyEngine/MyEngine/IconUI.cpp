#include "pch.h"
#include "IconUI.h"
#include "Texture.h"
#include "CameraMgr.h"
#include "MouseMgr.h"

IconUI* IconUI::selectedUI = nullptr;

IconUI::IconUI()
	: UI(false)
{
}

IconUI::~IconUI()
{
}

void IconUI::Initialize()
{
}

void IconUI::Update()
{
	UI* parentUI = GetParentUI();
	Vec2 mousePos = MOUSE_POS;

	Vec2 parentPos = parentUI->GetPos();
	Vec2 pos = parentPos + GetPos();

	if (pos.x <= mousePos.x && pos.x + TILE_SIZE >= mousePos.x &&
		pos.y <= mousePos.y && pos.y + TILE_SIZE >= mousePos.y)
	{
		if (IS_LBUTTON_CLICKED)
			selectedUI = this;
	}

	if (IS_RBUTTON_CLICKED)
		selectedUI = nullptr;
	
}

void IconUI::Render()
{	
	UI* parentUI = GetParentUI();
	if (nullptr != parentUI)
	{
		Texture* texture = parentUI->GetTexture();
		
		if (nullptr != texture)
		{
			Vec2 pos = parentUI->GetPos();
			pos += GetPos();

			TransparentBlt(
				BACK_BUF_DC,
				(int)(pos.x),
				(int)(pos.y),
				TILE_SIZE,
				TILE_SIZE,
				texture->GetDC(),
				(int)(mLT.x),
				(int)(mLT.y),
				TILE_SIZE,
				TILE_SIZE,
				RGB(255, 0, 255)
			);

			if (this == selectedUI)
			{
				Brush brush(BACK_BUF_DC, BRUSH_TYPE::HOLLOW);
				Pen pen(BACK_BUF_DC, PEN_TYPE::RED);

				Rectangle(BACK_BUF_DC,
					(int)pos.x, (int)pos.y, (int)(pos.x + TILE_SIZE), (int)(pos.y + TILE_SIZE));
			}
					
		}
	}


}

void IconUI::Destroy()
{
}
