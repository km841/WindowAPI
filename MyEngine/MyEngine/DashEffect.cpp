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
	// 0.015�ʸ��� 1���� ����ؾ� ��
	// 0.03�ʴ� �ӹ��Բ�
	// �ӹ��� �ð��� ����ؾ� ��
	// Ư�� ��ǥ�� �����ؼ� �� ��ǥ�� 0.3�ʸ�ŭ ���?
	// 
	// 0.015�ʸ��� Ư�� ��ǥ�� �����ϰ� �� ��ǥ�� 0.3�ʸ�ŭ ���

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
