#include "pch.h"
#include "BossAppearHUD.h"
#include "ResourceMgr.h"
#include "Texture.h"
#include "TimeMgr.h"

BossAppearHUD::BossAppearHUD()
	: mTex(nullptr)
	, mAlpha(0.f)
	, mBrightened(false)
	, mMaxDuration(1.0f)
	, mCurDuration(0.f)
	, mStayMaxDuration(2.0f)
	, mStayCurDuration(0.f)
{
	mTex = ResourceMgr::GetInstance().Load<Texture>(L"BossAppearCutton", L"Texture\\BossAppearCutton.bmp");

	mBlendFunc = {};
	mBlendFunc.BlendFlags = 0;
	mBlendFunc.AlphaFormat = AC_SRC_ALPHA;
	mBlendFunc.BlendOp = AC_SRC_OVER;
	mBlendFunc.SourceConstantAlpha = 0;

	SetPos(Vec2(0, 0));
}

BossAppearHUD::~BossAppearHUD()
{
}

void BossAppearHUD::Initialize()
{
	HUD::Initialize();
}

void BossAppearHUD::Update()
{
	if (GetState())
	{
		HUD::Update();

		if (mMaxDuration < mCurDuration)
		{
			mCurDuration = mMaxDuration;
			// 3ÃÊ ÈÄ¿¡ Brightned flag on
			if (mStayMaxDuration < mStayCurDuration)
			{
				mBrightened = true;
				mCurDuration = mMaxDuration - DT;
			}

			else
			{
				mStayCurDuration += DT;
			}
			
		}

		else
		{
			float ratio = mCurDuration / mMaxDuration;
			mBlendFunc.SourceConstantAlpha = (BYTE)(255.f * ratio);

			if (false == mBrightened)
			{
				mCurDuration += DT;
			}

			else
			{
				mCurDuration -= DT;
			}

			if (mCurDuration < 0.f)
			{
				SetState(false);
				mCurDuration = 0.f;
				mStayCurDuration = 0.f;
				mBrightened = false;
			}
		}

	}

}

void BossAppearHUD::Render()
{
	if (GetState())
	{
		if (nullptr != mTex)
		{
			Vec2 pos = GetPos();
			Vec2 texSize = mTex->GetSize();
			AlphaBlend(
				BACK_BUF_DC,
				(int)pos.x,
				(int)pos.y,
				(int)texSize.x,
				(int)texSize.y,
				mTex->GetDC(),
				0, 0,
				(int)texSize.x,
				(int)texSize.y,
				mBlendFunc
			);
		}
	}
}

void BossAppearHUD::Destroy()
{
}
