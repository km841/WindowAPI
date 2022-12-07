#include "pch.h"
#include "AfterImage.h"
#include "ResourceMgr.h"
#include "Texture.h"
#include "TimeMgr.h"
#include "CameraMgr.h"
#include "Animation.h"

AfterImage::AfterImage()
	: mAlpha(255.f)
	, mMaxDuration(.5f)
	, mCurDuration(0.f)
	, mDead(false)
{
	mTex = ResourceMgr::GetInstance().Load<Texture>(L"LaraBulletAnim", L"Texture\\LaraBulletAnim.bmp");
	mBlendFunc = {};
	mBlendFunc.BlendFlags = 0;
	mBlendFunc.AlphaFormat = AC_SRC_ALPHA;
	mBlendFunc.BlendOp = AC_SRC_OVER;
	mBlendFunc.SourceConstantAlpha = mAlpha;
}

AfterImage::~AfterImage()
{
}

void AfterImage::Initialize()
{
}

void AfterImage::Update()
{
	// 알파블렌딩 처리
	if (mCurDuration > mMaxDuration)
	{
		mDead = true;
	}
	else
	{
		mCurDuration += DT;
		float ratio = mCurDuration / mMaxDuration;
		mAlpha = (1.f - ratio) * 255.f;
		if (mAlpha < 1.f)
			mAlpha = 0.f;
		mBlendFunc.SourceConstantAlpha = mAlpha;
	}
}

void AfterImage::Render()
{
	// 이미지의 LT값을 받아서 처리

	if (!mDead)
	{
		AnimInfo info = mAnim->GetAnimInfo()[mFrm];

		Vec2 pos = RENDER_POS(GetPos());
		AlphaBlend(
			BACK_BUF_DC,
			pos.x - info.mSlice.x / 2.f,
			pos.y - info.mSlice.y / 2.f,
			info.mSlice.x,
			info.mSlice.y,
			mTex->GetDC(),
			info.mLeftTop.x,
			info.mLeftTop.y,
			info.mSlice.x,
			info.mSlice.y,
			mBlendFunc
		);
	}


}
