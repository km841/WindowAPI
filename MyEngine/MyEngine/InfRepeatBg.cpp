#include "pch.h"
#include "InfRepeatBg.h"
#include "TimeMgr.h"
#include "Texture.h"
#include "EventRegisteror.h"

InfRepeatBg::InfRepeatBg()
	: mSpeed(0.f)
	, mTexture(nullptr)
	, mChild(nullptr)
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
	Vec2 size = GetSize();

	if (pos.x <= -size.x)
	{
		SetPos(Vec2(size.x, 0.f));
	}
	else
	{
		pos.x -= mSpeed * DT;
		SetPos(pos);
	}
	
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