#include "pch.h"
#include "InfRepeatBg.h"
#include "TimeMgr.h"
#include "Texture.h"
#include "EventRegisteror.h"

InfRepeatBg::InfRepeatBg()
	: mSpeed(0.f)
{
}

InfRepeatBg::~InfRepeatBg()
{
}

InfRepeatBg::InfRepeatBg(const InfRepeatBg& _other)
	: mChild(nullptr)
	, mSpeed(_other.mSpeed)
{
	SetTexture(_other.GetTexture());
}

void InfRepeatBg::Initialize()
{
}

void InfRepeatBg::Update()
{
	if (nullptr == GetTexture())
		return;

	Vec2 pos = GetPos();
	pos.x -= mSpeed * DT;

	if (!mChild && pos.x <= -WINDOW_WIDTH_SIZE)
	{
		mChild = Clone();
		mChild->SetPos(Vec2(WINDOW_WIDTH_SIZE - (mSpeed * DT), 0.f));
		EventRegisteror::GetInstance().CreateObject(mChild, mChild->GetType());
	}

	if (pos.x <= -(WINDOW_WIDTH_SIZE * 2))
	{
		EventRegisteror::GetInstance().DeleteObject(this);
	}

	SetPos(pos);
}

void InfRepeatBg::Render()
{
	if (nullptr == GetTexture())
		return;

	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	TransparentBlt(
		BACK_BUF_DC,
		(int)pos.x,
		(int)pos.y,
		(int)size.x,
		(int)size.y,
		GetTexture()->GetDC(),
		0,
		0,
		(int)size.x,
		(int)size.y,
		RGB(255, 0, 255)
	);
}

void InfRepeatBg::Destroy()
{
}