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

	
	
	Vec2 size = GetSize();
	Vec2 mousePos = MOUSE_POS;

	if (mOnMouse)
	{
		if (mOnClicked)
		{
			g_Checked = this;
			//CallEvent();
		}
	}
}

void CheckButtonUI::Render()
{
	Vec2 size = GetSize();
	Texture* tex = GetTexture();
	UI* parentUI = GetParentUI();
	Vec2 pos = GetPos();

	if (nullptr != parentUI)
	{
		Vec2 parentPos = GetParentUI()->GetPos();
		pos += parentPos;
	}

	TextureInfo curInfo = {};
	
	if (g_Checked == this)
	{
		curInfo = mStates[(UINT)ButtonState::CHECKED];
	}
	else
	{
		curInfo = mStates[(UINT)ButtonState::NONE];
	}

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

bool CheckButtonUI::OnMouse()
{
	return ButtonUI::OnMouse();
}

bool CheckButtonUI::OnClicked()
{
	return mOnMouse && IS_LBUTTON_CLICKED;
}

void CheckButtonUI::Destroy()
{
}

void CheckButtonUI::TextureProcessing(Vec2 _leftTop, Vec2 _offset, Vec2 _size)
{
	mStates[(UINT)ButtonState::CHECKED] = { _leftTop, _offset, _size };
	mStates[(UINT)ButtonState::NONE] = { Vec2{_leftTop.x + _offset.x, _leftTop.y}, _offset, _size };
}
