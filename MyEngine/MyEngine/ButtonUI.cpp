#include "pch.h"
#include "ButtonUI.h"
#include "MouseMgr.h"
#include "Texture.h"

ButtonUI::ButtonUI()
	:UI(false)
{
	SetType(OBJECT_TYPE::UI);
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
	
	if (mOnMouse)
	{
		if (mEvent && mOnClicked)
			CallEvent();
	}
}

void ButtonUI::Render()
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	Texture* tex = GetTexture();

	TextureInfo curInfo = {};
	if (mOnMouse)
		curInfo = mStates[(UINT)ButtonState::MOUSE_ON];
	else
		curInfo = mStates[(UINT)ButtonState::NONE];

	TransparentBlt(BACK_BUF_DC,
		(int)(pos.x - (curInfo.mSize.x / 2.f)),
		(int)(pos.y - (curInfo.mSize.y / 2.f)),
		(int)(curInfo.mSize.x),
		(int)(curInfo.mSize.y),
		tex->GetDC(),
		(int)(curInfo.mLeftTop.x),
		(int)(curInfo.mLeftTop.y),
		(int)(curInfo.mSize.x),
		(int)(curInfo.mSize.y),
		RGB(255, 0, 255)
	);
}

void ButtonUI::Destroy()
{
}

bool ButtonUI::OnMouse()
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	Vec2 mousePos = MOUSE_POS;
	return (pos.x - (size.x / 2.f) <= mousePos.x
		&& pos.x + (size.x / 2.f) >= mousePos.x
		&& pos.y - (size.y / 2.f) <= mousePos.y
		&& pos.y + (size.y / 2.f) >= mousePos.y);
}

bool ButtonUI::OnClicked()
{
	return OnMouse() && IS_LBUTTON_CLICKED;
}

void ButtonUI::TextureProcessing(Vec2 _leftTop, Vec2 _offset, Vec2 _size)
{
	mStates[(UINT)ButtonState::MOUSE_ON] = { _leftTop, _offset, _size };
	mStates[(UINT)ButtonState::NONE] = { Vec2{_leftTop.x + _offset.x, _leftTop.y}, _offset, _size };
}


