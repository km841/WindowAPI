#include "pch.h"
#include "CheckButtonUI.h"
#include "MouseMgr.h"
#include "Texture.h"

CheckButtonUI* CheckButtonUI::g_Checked = nullptr;
CheckButtonUI::CheckButtonUI()
{
}

CheckButtonUI::~CheckButtonUI()
{
}

void CheckButtonUI::Initialize()
{
	
}

void CheckButtonUI::Update()
{
	Vec2 parentPos = GetParentUI()->GetPos();
	Vec2 pos = parentPos + GetPos();
	Vec2 size = GetSize();
	Vec2 mousePos = MOUSE_POS;

	if (pos.x - (size.x / 2.f) <= mousePos.x
		&& pos.x + (size.x / 2.f) >= mousePos.x
		&& pos.y - (size.y / 2.f) <= mousePos.y
		&& pos.y + (size.y / 2.f) >= mousePos.y)
	{
		if (mEvent && IS_LBUTTON_CLICKED)
		{
			g_Checked = this;
			CallEvent();
		}
	}
}

void CheckButtonUI::Render()
{
	Vec2 parentPos = GetParentUI()->GetPos();
	Vec2 pos = parentPos + GetPos();
	Vec2 size = GetSize();
	Texture* tex = GetTexture();

	if (g_Checked == this)
	{
		TransparentBlt(BACK_BUF_DC,
			(int)(pos.x - (mStates[(UINT)ButtonState::CHECKED].mSize.x / 2.f)),
			(int)(pos.y - (mStates[(UINT)ButtonState::CHECKED].mSize.y / 2.f)),
			(int)(mStates[(UINT)ButtonState::CHECKED].mSize.x),
			(int)(mStates[(UINT)ButtonState::CHECKED].mSize.y),
			tex->GetDC(),
			(int)(mStates[(UINT)ButtonState::CHECKED].mLeftTop.x),
			(int)(mStates[(UINT)ButtonState::CHECKED].mLeftTop.y),
			(int)(mStates[(UINT)ButtonState::CHECKED].mSize.x),
			(int)(mStates[(UINT)ButtonState::CHECKED].mSize.y),
			RGB(255, 0, 255)
		);
	}

	else
	{
		TransparentBlt(BACK_BUF_DC,
			(int)(pos.x - (mStates[(UINT)ButtonState::NONE].mSize.x / 2.f)),
			(int)(pos.y - (mStates[(UINT)ButtonState::NONE].mSize.y / 2.f)),
			(int)(mStates[(UINT)ButtonState::NONE].mSize.x),
			(int)(mStates[(UINT)ButtonState::NONE].mSize.y),
			tex->GetDC(),
			(int)(mStates[(UINT)ButtonState::NONE].mLeftTop.x),
			(int)(mStates[(UINT)ButtonState::NONE].mLeftTop.y),
			(int)(mStates[(UINT)ButtonState::NONE].mSize.x),
			(int)(mStates[(UINT)ButtonState::NONE].mSize.y),
			RGB(255, 0, 255)
		);
	}
}

void CheckButtonUI::Destroy()
{
}

void CheckButtonUI::TextureProcessing(Vec2 _leftTop, Vec2 _offset, Vec2 _size)
{
	mStates[(UINT)ButtonState::CHECKED] = { _leftTop, _offset, _size };
	mStates[(UINT)ButtonState::NONE] = { Vec2{_leftTop.x + _offset.x, _leftTop.y}, _offset, _size };
}
