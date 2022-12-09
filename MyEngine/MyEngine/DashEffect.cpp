#include "pch.h"
#include "DashEffect.h"
#include "Texture.h"
#include "TimeMgr.h"
#include "CameraMgr.h"
#include "Player.h"

DashEffect::DashEffect()
	: mStayTime(0.3f)
	, mCurStayTime(0.3f)


{
	mBlendFunc = {};
	mBlendFunc.BlendFlags = 0;
	mBlendFunc.AlphaFormat = AC_SRC_ALPHA;
	mBlendFunc.BlendOp = AC_SRC_OVER;
	mBlendFunc.SourceConstantAlpha = 100;
}

DashEffect::~DashEffect()
{
}

void DashEffect::Update()
{
	// mDuration = 0.015f;

	if (mStayTime > mCurStayTime)
	{
		mCurStayTime += DT;
		float ratio = mCurStayTime / mStayTime;
		mAlpha = 100.f * (1.f - ratio);
		mBlendFunc.SourceConstantAlpha = (BYTE)mAlpha;
	}
}

void DashEffect::Render()
{
	// 0.015초마다 1번씩 출력해야 함
	// 0.03초는 머물게끔
	// 머무는 시간도 고려해야 함
	// 특정 좌표를 지정해서 그 좌표에 0.3초만큼 출력?
	// 
	// 0.015초마다 특정 좌표를 저장하고 그 좌표에 0.3초만큼 출력

	Texture* tex = GetTexture();
	if (nullptr != tex)
	{
		if (mStayTime > mCurStayTime)
		{
			Vec2 pos = RENDER_POS(GetPos());
			Vec2 size = GetSize();
			Vec2 ltPos = {};
			DIR playerDir = Player::GetPlayer()->GetPlayerDir();

			switch (playerDir)
			{
			case DIR::LEFT:
				ltPos = Vec2(0.f, 0.f);
				break;

			case DIR::RIGHT:
				ltPos = Vec2(0.f, 96.f);
				break;
			}

			AlphaBlend(
				BACK_BUF_DC,
				(int)(pos.x - size.x / 2.f),
				(int)(pos.y - size.y),
				(int)size.x,
				(int)size.y,
				tex->GetDC(),
				(int)ltPos.x,
				(int)ltPos.y,
				(int)(size.x),
				(int)(size.y),
				mBlendFunc
			);
		}

	}
}

void DashEffect::Reset()
{
	mCurStayTime = 0.f;
}
