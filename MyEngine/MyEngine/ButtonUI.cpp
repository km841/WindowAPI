#include "pch.h"
#include "ButtonUI.h"
#include "MouseMgr.h"
#include "Texture.h"

ButtonUI::ButtonUI()
	:UI(false)
{
}

ButtonUI::~ButtonUI()
{
}

void ButtonUI::Initialize()
{

}

void ButtonUI::Update()
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	Vec2 mousePos = MOUSE_POS;
	
	if (pos.x - (size.x / 2.f) <= mousePos.x 
		&& pos.x + (size.x / 2.f) >= mousePos.x
		&& pos.y - (size.y / 2.f) <= mousePos.y
		&& pos.y + (size.y / 2.f) >= mousePos.y)
	{
		mOnMouse = true;

		if (mEvent && IS_LBUTTON_CLICKED)
		{
			CallEvent();
		}
	}
	else
	{
		mOnMouse = false;
	}
}

void ButtonUI::Render()
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	Texture* tex = GetTexture();

	if (mOnMouse)
	{
		TransparentBlt(BACK_BUF_DC,
			(int)(pos.x - (mStates[(UINT)ButtonState::MOUSE_ON].mSize.x / 2.f)),
			(int)(pos.y - (mStates[(UINT)ButtonState::MOUSE_ON].mSize.y / 2.f)),
			(int)(mStates[(UINT)ButtonState::MOUSE_ON].mSize.x),
			(int)(mStates[(UINT)ButtonState::MOUSE_ON].mSize.y),
			tex->GetDC(),
			(int)(mStates[(UINT)ButtonState::MOUSE_ON].mLeftTop.x),
			(int)(mStates[(UINT)ButtonState::MOUSE_ON].mLeftTop.y),
			(int)(mStates[(UINT)ButtonState::MOUSE_ON].mSize.x),
			(int)(mStates[(UINT)ButtonState::MOUSE_ON].mSize.y),
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

void ButtonUI::Destroy()
{
}

void ButtonUI::TextureProcessing(Vec2 _leftTop, Vec2 _offset, Vec2 _size)
{
	mStates[(UINT)ButtonState::MOUSE_ON] = { _leftTop, _offset, _size };
	mStates[(UINT)ButtonState::NONE] = { Vec2{_leftTop.x + _offset.x, _leftTop.y}, _offset, _size };
}
