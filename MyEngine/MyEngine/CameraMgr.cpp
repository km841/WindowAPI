#include "pch.h"
#include "CameraMgr.h"
#include "TimeMgr.h"
#include "GameObject.h"
#include "KeyMgr.h"
#include "ResourceMgr.h"
#include "Texture.h"

void CameraMgr::Initialize()
{
	Vec2 resolution = APP_INSTANCE.GetResolution();
	mLookPos = resolution / 2.f;

	mCutton = ResourceMgr::GetInstance().CreateTexture(L"Cutton", Vec2(WINDOW_WIDTH_SIZE, WINDOW_HEIGHT_SIZE));

	mBlendFunc = {};
	mBlendFunc.BlendFlags = 0;
	mBlendFunc.AlphaFormat = 0;
	mBlendFunc.BlendOp = AC_SRC_OVER;
	mBlendFunc.SourceConstantAlpha = 0;

	mEndTime = 5.0f;
	
	mEffect = CAMERA_EFFECT::END;
}

void CameraMgr::Update()
{
	if (mEffect != CAMERA_EFFECT::END)
	{
		if (mAlphaTime >= mEndTime)
			mEffect = CAMERA_EFFECT::END;

		mAlphaTime += DT;
		float ratio = mAlphaTime / mEndTime;

		switch (mEffect)
		{
		case CAMERA_EFFECT::FADE_IN:
			mAlphaValue = 1.0f - ratio;
			mBlendFunc.SourceConstantAlpha = (BYTE)(255.f * mAlphaValue);
			break;

		case CAMERA_EFFECT::FADE_OUT:
			mAlphaValue = ratio;
			mBlendFunc.SourceConstantAlpha = (BYTE)(255.f * mAlphaValue);
			break;
		}
	}

	if (nullptr != mObject)
	{
		if (mObject->GetType() == OBJECT_TYPE::PLAYER)
		{
			Vec2 pos = mObject->GetPos();
			mLookPos = pos + Vec2(0.f, -160.f);
		}
		else
		{
			mLookPos = mObject->GetPos();
		}
	}

	if (IS_PRESSED(KEY::W))
	{
		mLookPos.y -= 600 * DT;
	}
	if (IS_PRESSED(KEY::S))
	{
		mLookPos.y += 600 * DT;
	}
	if (IS_PRESSED(KEY::A))
	{
		mLookPos.x -= 600 * DT;
	}
	if (IS_PRESSED(KEY::D))
	{
		mLookPos.x += 600 * DT;
	}

	WorldToScreenCalc();
}

void CameraMgr::Render()
{
	if (mEffect != CAMERA_EFFECT::END)
	{
		AlphaBlend(BACK_BUF_DC,
			0, 0,
			WINDOW_WIDTH_SIZE, WINDOW_HEIGHT_SIZE,
			mCutton->GetDC(),
			0, 0,
			mCutton->GetWidth(),
			mCutton->GetHeight(),
			mBlendFunc);
	}
}

Vec2 CameraMgr::GetTileCoord(Vec2 _tilePos) const
{
	Vec2 calVec = {0, 0};
	while (true)
	{
		if (calVec.x + TILE_SIZE >= _tilePos.x &&
			calVec.y + TILE_SIZE >= _tilePos.y)
			break;

		if (calVec.x + TILE_SIZE < _tilePos.x)
			calVec.x += TILE_SIZE;

		if (calVec.y + TILE_SIZE < _tilePos.y)
			calVec.y += TILE_SIZE;
	}

	return calVec;
}

Vec2 CameraMgr::GetIconUIPos(Vec2 _uiPos, int _index) const
{
	int offset = _index * (TILE_SIZE * 3);
	return Vec2(_uiPos.x, _uiPos.y - offset);
}

void CameraMgr::WorldToScreenCalc()
{
	mAccTime += DT;
	Vec2 resolution = APP_INSTANCE.GetResolution();
	Vec2 center = resolution / 2.f;
	mDistance = mLookPos - center;
}

void CameraMgr::SetEffect(CAMERA_EFFECT _effect, float _endTime)
{
	mEffect = _effect;
	mEndTime = _endTime;
	mAlphaTime = 0.0f;
}
