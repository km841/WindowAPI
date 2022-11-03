#include "pch.h"
#include "BackgroundUI.h"
#include "TimeMgr.h"
#include "Texture.h"
#include "EventRegisteror.h"

BackgroundUI::BackgroundUI()
	:UI(false)
	,mSpeed(0.f)
{
}

BackgroundUI::~BackgroundUI()
{
}

void BackgroundUI::Initialize()
{
}

void BackgroundUI::Update()
{
	if (nullptr == mTexture)
		return;

	Vec2 pos = GetPos();
	pos.x -= mSpeed * DT;

	if (!mChild && pos.x <= -WINDOW_WIDTH_SIZE)
	{
		mChild = new BackgroundUI;
		mChild->SetTexture(mTexture);
		mChild->SetSize(GetSize());
		mChild->SetSpeed(mSpeed);
		mChild->SetPos(Vec2(WINDOW_WIDTH_SIZE - (mSpeed * DT), 0.f));
		mChild->SetType(GetType());

		EventRegisteror::GetInstance().CreateObject(mChild, GetType());
	}

	if (pos.x <= -(WINDOW_WIDTH_SIZE * 2))
	{
		EventRegisteror::GetInstance().DeleteObject(this);
	}

	SetPos(pos);
}

void BackgroundUI::Render()
{
	if (nullptr == mTexture)
		return;

	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	TpBltRapper(
		Vec2(pos.x, pos.y),
		Vec2(size.x, size.y),
		Vec2(0, 0),
		Vec2(size.x, size.y)
	);


}

void BackgroundUI::Destroy()
{
}

void BackgroundUI::SetTexture(Texture* _tex)
{
	mTexture = _tex;
}

void BackgroundUI::TpBltRapper(Vec2 _dstLT, Vec2 _dstSize, Vec2 _srcLT, Vec2 _srcSize)
{
	TransparentBlt(
		BACK_BUF_DC,
		(int)_dstLT.x,
		(int)_dstLT.y,
		(int)_dstSize.x,
		(int)_dstSize.y,
		mTexture->GetDC(),
		(int)_srcLT.x,
		(int)_srcLT.y,
		(int)_srcSize.x,
		(int)_srcSize.y,
		RGB(255, 0, 255)
	);
}
