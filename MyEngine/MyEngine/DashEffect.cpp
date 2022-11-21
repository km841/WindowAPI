#include "pch.h"
#include "DashEffect.h"
#include "Texture.h"
#include "TimeMgr.h"
#include "CameraMgr.h"
#include "Player.h"

DashEffect::DashEffect()
	: mCurDuration(0.f)
	, mDuration(0.017f)
	, mStayTime(0.04f)
	, mCurStayTime(0.f)
	, mImgCount(AFTER_IMAGE_TOTAL)
	, mCurImg(AFTER_IMAGE_TOTAL)
	, mStayPos{}
{

	mBlendFunc = {};
	mBlendFunc.BlendFlags = 0;
	mBlendFunc.AlphaFormat = AC_SRC_ALPHA;
	mBlendFunc.BlendOp = AC_SRC_OVER;
	mBlendFunc.SourceConstantAlpha = 70;
}

DashEffect::~DashEffect()
{
}

void DashEffect::Update()
{
	// mDuration = 0.015f;
	if (mImgCount < AFTER_IMAGE_TOTAL)
	{
		if (mDuration > mCurDuration)
		{
			mCurDuration += DT;
		}
		else
		{
			mStayPos[mImgCount] = GetOwner()->GetPos();
			mImgCount++;
			mCurDuration = 0.f;
		}
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
	if (nullptr != tex && mCurImg < AFTER_IMAGE_TOTAL)
	{
		if (Vec2(0.f, 0.f) != mStayPos[mCurImg])
		{
			if (mStayTime > mCurStayTime)
			{
				Vec2 mCurPos = RENDER_POS(mStayPos[mCurImg]);
				Vec2 size = GetSize();
				Vec2 ltPos = {};
				PLAYER_DIR playerDir = Player::GetPlayer()->GetPlayerDir();

				switch (playerDir)
				{
				case PLAYER_DIR::LEFT:
					ltPos = Vec2(0.f, 0.f);
					break;

				case PLAYER_DIR::RIGHT:
					ltPos = Vec2(0.f, 32.f);
					break;
				}

				AlphaBlend(
					BACK_BUF_DC,
					mCurPos.x - size.x / 2.f,
					mCurPos.y - size.y,
					size.x,
					size.y,
					tex->GetDC(),
					ltPos.x,
					ltPos.y,
					size.x / TIMES,
					size.y / TIMES,
					mBlendFunc
				);

				mCurStayTime += DT;
			}

			else
			{
				mCurImg++;
				mCurStayTime = 0.f;
			}

		}
	}
}

void DashEffect::Reset()
{
	mImgCount = 0.f;
	mCurImg = 0.f;
	mCurStayTime = 0.f;
	mCurDuration = 0.f;
	for (int i = 0; i < AFTER_IMAGE_TOTAL; ++i)
	{
		mStayPos[i] = Vec2{0.f, 0.f};
	}
}
