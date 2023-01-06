#include "pch.h"
#include "GuideHUD.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "TimeMgr.h"

GuideHUD::GuideHUD()
	: mComeBegin(false)
	, mComeMaxTime(1.0f)
	, mComeCurTime(0.f)
	, mComeComplete(false)
	, mBackMaxTime(0.15f)
	, mBackCurTime(0.f)
	, mBackComplete(false)
	, mStayMaxTime(2.f)
	, mStayCurTime(0.f)
	, mStayComplete(false)
	, mLeaveMaxTime(2.f)
	, mLeaveCurTime(0.f)
{

}

GuideHUD::~GuideHUD()
{
}

void GuideHUD::Initialize()
{
	HUD::Initialize();
}

void GuideHUD::Update()
{
	if (GetState())
	{
		Vec2 curPos = GetPos();

		if (false == mComeComplete && 
			false == mComeBegin)
		{
			mComeBegin = true;
		}

		else
		{
			if (mComeMaxTime < mComeCurTime)
			{
				mComeComplete = true;
			}

			else
			{
				mComeCurTime += DT;
				curPos.x += 900.f * DT;
				
			}
		}

		if (false == mBackComplete &&
			true == mComeComplete)
		{
			if (mBackMaxTime < mBackCurTime)
			{
				mBackComplete = true;
			}

			else
			{
				mBackCurTime += DT;
				curPos.x -= 1200.f * DT;
			}
		}

		if (false == mStayComplete &&
			true == mBackComplete)
		{
			if (mStayMaxTime < mStayCurTime)
			{
				mStayComplete = true;
			}

			else
			{
				mStayCurTime += DT;
			}
		}

		if (mStayComplete)
		{
			if (mLeaveMaxTime < mLeaveCurTime)
			{
				
			    SetState(false);
			}

			else
			{
				mLeaveCurTime += DT;
				curPos.x -= 1200.f * DT;
			}
		}

		SetPos(curPos);
		HUD::Update();

	}

}

void GuideHUD::Render()
{
	if (GetState())
	{

		if (nullptr != mTex)
		{
			Vec2 curPos = GetPos();
			Vec2 orgSize = mTex->GetSize();
			Vec2 size = orgSize / 1.5f;

			TransparentBlt(
				BACK_BUF_DC,
				(int)(curPos.x - size.x / 2.f),
				(int)(curPos.y - size.y / 2.f),
				(int)(size.x),
				(int)(size.y),
				mTex->GetDC(),
				0, 0,
				(int)orgSize.x,
				(int)orgSize.y,
				RGB_MAGENTA
			);



		}


		HUD::Render();

	}
}

void GuideHUD::Destroy()
{
	HUD::Destroy();
}

void GuideHUD::SetupType(SCENE_TYPE _type)
{
	mComeBegin = false;
	mComeComplete = false;
	mBackComplete = false;
	mStayComplete = false;
	mLeaveCurTime = 0.f;
	mStayCurTime = 0.f;
	mBackCurTime = 0.f;
	mComeCurTime = 0.f;

	switch (_type)
	{
	case SCENE_TYPE::TOWN:
		mTex = LOAD_TEXTURE(L"TownGuide", L"Texture\\TownGuide.bmp");
		break;

	case SCENE_TYPE::DUNGEON:
		mTex = LOAD_TEXTURE(L"DungeonGuide", L"Texture\\DungeonGuide.bmp");
		break;
	}
	
	if (nullptr != mTex)
	{
		SetPos(Vec2(-50, 250));
	}
	
	
}
