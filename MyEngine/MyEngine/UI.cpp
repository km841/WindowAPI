#include "pch.h"
#include "UI.h"
#include "KeyMgr.h"

UI::UI(bool _camMode)
	: mCamMode(_camMode)
	, mOnMouse(false)
	, mClicked(false)
{
	
}

UI::~UI()
{
}

void UI::Initialize()
{
}

void UI::Update()
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	Vec2 mousePos = MOUSE_POS;

	if (mousePos.x >= pos.x && mousePos.x <= pos.x + size.x &&
		mousePos.y >= pos.y && mousePos.y <= pos.y + size.y)
	{
		mOnMouse = true;
	}
	else
		mOnMouse = false;
}

void UI::Render()
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	if (mOnMouse)
	{
		Pen pen(BACK_BUF_DC, PEN_TYPE::GREEN);
		Rectangle(BACK_BUF_DC
			, (int)(pos.x)
			, (int)(pos.y)
			, (int)(pos.x + size.x)
			, (int)(pos.x + size.y));
	}
	else
	{
		Rectangle(BACK_BUF_DC
			, (int)(pos.x)
			, (int)(pos.y)
			, (int)(pos.x + size.x)
			, (int)(pos.x + size.y));
	}


}

void UI::Destroy()
{
}
