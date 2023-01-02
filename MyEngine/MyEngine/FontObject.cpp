#include "pch.h"
#include "FontObject.h"
#include "CameraMgr.h"
#include "Texture.h"
#include "TimeMgr.h"

FontObject::FontObject(bool _trans)
	: mMaxDuration(0.2f)
	, mCurDuration(0.f)
	, mAlpha(1.f)
	, mDead(false)
	, mTrans(_trans)
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
	// ���İ� ���� ������ 135�� ������ �� ������ ��
	// 1-RATIO�� ���ؼ� ���� �������� ��������

	if (mTrans)
	{
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

}

void FontObject::Render()
{
	Vec2 pos = RENDER_POS(GetPos());
	// �������� ����Ϸ��� Texture�� �־�� ��

	Vec2 orgSize = mTex->GetSize();
	Vec2 size = orgSize * 1.5f;
	if (mTrans)
	{
		AlphaBlend(
			BACK_BUF_DC,
			(int)(pos.x - size.x / 2.f),
			(int)(pos.y - size.y / 2.f),
			(int)(size.x),
			(int)(size.y),
			mTex->GetDC(),
			0, 0,
			(int)orgSize.x,
			(int)orgSize.y,
			mBlendFunc
		);
	}

	else
	{

	}

}
