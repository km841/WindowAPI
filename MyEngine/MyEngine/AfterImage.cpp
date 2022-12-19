#include "pch.h"
#include "AfterImage.h"
#include "ResourceMgr.h"
#include "Texture.h"
#include "TimeMgr.h"
#include "CameraMgr.h"
#include "Animation.h"
#include "EventRegisteror.h"

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
	mBlendFunc.SourceConstantAlpha = (BYTE)mAlpha;
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
		mBlendFunc.SourceConstantAlpha = (BYTE)mAlpha;
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
			(int)(pos.x - info.mSlice.x / 2.f),
			(int)(pos.y - info.mSlice.y / 2.f),
			(int)(info.mSlice.x),
			(int)(info.mSlice.y),
			mTex->GetDC(),
			(int)(info.mLeftTop.x),
			(int)(info.mLeftTop.y),
			(int)(info.mSlice.x),
			(int)(info.mSlice.y),
			mBlendFunc
		);
	}


}
