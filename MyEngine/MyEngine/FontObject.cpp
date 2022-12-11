#include "pch.h"
#include "FontObject.h"
#include "CameraMgr.h"
#include "Texture.h"
#include "TimeMgr.h"

FontObject::FontObject()
	: mMaxDuration(0.2f)
	, mCurDuration(0.f)
	, mAlpha(1.f)
	, mDead(false)
{
	mBlendFunc = {};
	mBlendFunc.BlendFlags = 0;
	mBlendFunc.AlphaFormat = AC_SRC_ALPHA;
	mBlendFunc.BlendOp = AC_SRC_OVER;
	mBlendFunc.SourceConstantAlpha = (BYTE)255.f;
}

FontObject::~FontObject()
{
}

void FontObject::Initialize()
{

}

void FontObject::Update()
{
	// 알파값 현재 각도를 135로 나눠서 그 비율로 함
	// 1-RATIO로 구해서 점점 옅어지는 방향으로
	if (mMaxDuration > mCurDuration)
	{
		mCurDuration += DT;
	}
	else
	{
		mAlpha -= DT;
		if (0.f >= mAlpha)
		{
			mAlpha = 0.f;
			mDead = true;
		}

		mBlendFunc.SourceConstantAlpha = (BYTE)(mAlpha * 255.f);
	}
}

void FontObject::Render()
{
	Vec2 pos = RENDER_POS(GetPos());
	// 데미지를 출력하려면 Texture가 있어야 함

	Vec2 size = mTex->GetSize();

	//Rectangle(BACK_BUF_DC,
	//	pos.x - 15,
	//	pos.y - 15,
	//	pos.x + 15,
	//	pos.y + 15);

	//BitBlt(
	//	BACK_BUF_DC,
	//	pos.x - 15,
	//	pos.y - 15,
	//	size.x,
	//	size.y,
	//	mTex->GetDC(),
	//	0, 0,
	//	SRCCOPY
	//);

	AlphaBlend(
		BACK_BUF_DC,
		(int)(pos.x - size.x / 2.f),
		(int)(pos.y - size.y / 2.f),
		(int)(size.x),
		(int)(size.y),
		mTex->GetDC(),
		0, 0,
		(int)size.x,
		(int)size.y,
		mBlendFunc
	);
}
