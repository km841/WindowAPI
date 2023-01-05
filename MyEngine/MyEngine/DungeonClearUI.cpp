#include "pch.h"
#include "DungeonClearUI.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "TimeMgr.h"


DungeonClearUI::DungeonClearUI()
	: UI(false)
	, mTex(nullptr)
	, mSuccessTex(nullptr)
	, mBaseTex(nullptr)
	, mClearLogBegin(false)
	, mSuccessUIBegin(false)
	, mSuccessUIShowComplete(false)
	, mSuccessUIMoveComplete(false)
	, mDistance(0.f)
	, mSpeed(0.f)
	, mSuccessUIShowMaxTime(2.f)
	, mSuccessUIShowCurTime(0.f)
	, mSuccessUIMoveMaxTime(2.f)
	, mSuccessUIMoveCurTime(0.f)
	, mClearLogShowMaxTime(2.f)
	, mClearLogShowCurTime(0.f)
	, mClearUIComplete(false)
{
	SetType(OBJECT_TYPE::UNIQUE_UI);
	SetUIType(UI_TYPE::DUNGEON_CLEAR);

	

	mSuccessUIBlendFunc = {};
	mSuccessUIBlendFunc.BlendFlags = 0;
	mSuccessUIBlendFunc.AlphaFormat = AC_SRC_ALPHA;
	mSuccessUIBlendFunc.BlendOp = AC_SRC_OVER;
	mSuccessUIBlendFunc.SourceConstantAlpha = 0;

	mLogUIBlendFunc = {};
	mLogUIBlendFunc.BlendFlags = 0;
	mLogUIBlendFunc.AlphaFormat = AC_SRC_ALPHA;
	mLogUIBlendFunc.BlendOp = AC_SRC_OVER;
	mLogUIBlendFunc.SourceConstantAlpha = 0;

	mBaseBlendFunc = {};
	mBaseBlendFunc.BlendFlags = 0;
	mBaseBlendFunc.AlphaFormat = 0;
	mBaseBlendFunc.BlendOp = AC_SRC_OVER;
	mBaseBlendFunc.SourceConstantAlpha = 200;

	mTex = LOAD_TEXTURE(L"DungeonClearTex", L"Texture\\DungeonClear_UI.bmp");
	mSuccessTex = LOAD_TEXTURE(L"DungeonSuccessTex", L"Texture\\DungeonSuccessTex.bmp");
	mBaseTex = ResourceMgr::GetInstance().CreateTexture(L"DungeonClearBase", Vec2(WINDOW_WIDTH_SIZE, WINDOW_HEIGHT_SIZE));

	mSuccessUIPos = Vec2(0.f, WINDOW_HEIGHT_SIZE / 2.f - mSuccessTex->GetHeight() / 2.f);
	mSpeed = mSuccessUIPos.y / mSuccessUIMoveMaxTime;
}

DungeonClearUI::~DungeonClearUI()
{
}

void DungeonClearUI::Initialize()
{
}

void DungeonClearUI::Update()
{
	if (GetState())
	{
		if (false == mSuccessUIBegin &&
			false == mSuccessUIShowComplete)
		{
			mSuccessUIBegin = true;
		}

		else
		{
			if (mSuccessUIShowMaxTime < mSuccessUIShowCurTime)
			{
				mSuccessUIShowComplete = true;
				mSuccessUIBlendFunc.SourceConstantAlpha = (BYTE)255.f;
			}

			else
			{
				float ratio = mSuccessUIShowCurTime / mSuccessUIShowMaxTime;
				mSuccessUIBlendFunc.SourceConstantAlpha = (BYTE)(255.f * ratio);
				mSuccessUIShowCurTime += DT;
				// 알파값 조절
			}
		}


		if (false == mSuccessUIMoveComplete &&
			true == mSuccessUIShowComplete)
		{
			if (mSuccessUIMoveMaxTime < mSuccessUIMoveCurTime)
			{
				mSuccessUIMoveComplete = true;
			}

			else
			{
				mSuccessUIMoveCurTime += DT;
				mSuccessUIPos.y -= mSpeed * DT;
				// ui 움직이기
			}
		}

		if (false == mClearUIComplete &&
			true == mSuccessUIMoveComplete)
		{
			if (false == mClearLogBegin)
			{
				mClearLogBegin = true;
			}

			else
			{
				if (mClearLogShowMaxTime < mClearLogShowCurTime)
				{
					mClearLogShowCurTime = mClearLogShowMaxTime;
					mClearUIComplete = true;
				}
				else
				{
					float ratio = mClearLogShowCurTime / mClearLogShowMaxTime;
					mLogUIBlendFunc.SourceConstantAlpha = (BYTE)(255.f * ratio);
					mClearLogShowCurTime += DT;
					// 알파값 조절
				}
			}
		}

		UI::Update();
	}
	



}

void DungeonClearUI::Render()
{
	if (GetState())
	{
		if (nullptr != mBaseTex && nullptr != mTex)
		{
			Vec2 baseSize = mBaseTex->GetSize();
			Vec2 texSize = mTex->GetSize();
			Vec2 successSize = mSuccessTex->GetSize();

			AlphaBlend(
				BACK_BUF_DC,
				0, 0,
				baseSize.x,
				baseSize.y,
				mBaseTex->GetDC(),
				0, 0,
				baseSize.x,
				baseSize.y,
				mBaseBlendFunc
			);

			if (mClearLogBegin)
			{
				AlphaBlend(
					BACK_BUF_DC,
					0, 0,
					texSize.x,
					texSize.y,
					mTex->GetDC(),
					0, 0,
					texSize.x,
					texSize.y,
					mLogUIBlendFunc
				);
			}

			if (mSuccessUIBegin)
			{
				AlphaBlend(
					BACK_BUF_DC,
					mSuccessUIPos.x,
					mSuccessUIPos.y,
					successSize.x,
					successSize.y,
					mSuccessTex->GetDC(),
					0, 0,
					successSize.x,
					successSize.y,
					mSuccessUIBlendFunc
				);
			}
		}


		UI::Render();
	}
}
