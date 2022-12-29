#include "pch.h"
#include "BossAppearHUD.h"
#include "ResourceMgr.h"
#include "Texture.h"
#include "TimeMgr.h"
#include "FontMgr.h"
#include "BossMonster.h"

BossAppearHUD::BossAppearHUD()
	: mTex(nullptr)
	, mAlpha(0.f)
	, mBrightened(false)
	, mMaxDuration(1.0f)
	, mCurDuration(0.f)
	, mStayMaxDuration(2.0f)
	, mStayCurDuration(0.f)
	, mBossNameTex(nullptr)
	, mBossCommentTex(nullptr)
{
	mTex = ResourceMgr::GetInstance().Load<Texture>(L"BossAppearCutton", L"Texture\\BossAppearCutton.bmp");

	mBlendFunc = {};
	mBlendFunc.BlendFlags = 0;
	mBlendFunc.AlphaFormat = AC_SRC_ALPHA;
	mBlendFunc.BlendOp = AC_SRC_OVER;
	mBlendFunc.SourceConstantAlpha = 0;

	SetPos(Vec2(0, 0));
	mBossNamePos = Vec2(100, 570);
	mBossCommentPos = Vec2(100, 520);
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

			if (nullptr != mBossNameTex)
			{
				Vec2 bossNameOrgSize = mBossNameTex->GetSize();
				Vec2 bossNameSize = mBossNameTex->GetSize() * 2.f;

				AlphaBlend(
					BACK_BUF_DC,
					mBossNamePos.x - bossNameSize.x / 2.f,
					mBossNamePos.y - bossNameSize.y / 2.f,
					bossNameSize.x,
					bossNameSize.y,
					mBossNameTex->GetDC(),
					0, 0,
					bossNameOrgSize.x,
					bossNameOrgSize.y,
					mBlendFunc
				);
			}

			if (nullptr != mBossCommentTex)
			{
				Vec2 bossCommentSize = mBossCommentTex->GetSize();

				AlphaBlend(
					BACK_BUF_DC,
					mBossCommentPos.x - bossCommentSize.x / 2.f,
					mBossCommentPos.y - bossCommentSize.y / 2.f,
					bossCommentSize.x,
					bossCommentSize.y,
					mBossCommentTex->GetDC(),
					0, 0,
					bossCommentSize.x,
					bossCommentSize.y,
					mBlendFunc
				);
			}

		}
	}
}

void BossAppearHUD::Destroy()
{
}

void BossAppearHUD::SetBossMonster(BossMonster* _boss)
{
	if (nullptr == _boss)
		return;

	mBoss = _boss;
	
	mBossNameTex = FontMgr::GetInstance().GetTextTexture(mBoss->GetBossName(), mBoss->GetBossName());
	if (nullptr != mBossNameTex)
	{
		mBossNameTex->SetAlphaValue(RGB_MAGENTA, 0);
		mBossNameTex->SetAlphaValue(RGB_WHITE, 255);
	}

	mBossCommentTex = FontMgr::GetInstance().GetTextTexture(mBoss->GetBossComment(), mBoss->GetBossComment());
	if (nullptr != mBossCommentTex)
	{
		mBossCommentTex->SetAlphaValue(RGB_MAGENTA, 0);
		mBossCommentTex->SetAlphaValue(RGB_WHITE, 255);
	}
}
