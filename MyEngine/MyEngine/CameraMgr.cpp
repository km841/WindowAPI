#include "pch.h"
#include "CameraMgr.h"
#include "TimeMgr.h"
#include "GameObject.h"
#include "KeyMgr.h"
#include "ResourceMgr.h"
#include "Texture.h"
#include "MouseMgr.h"

CameraMgr::CameraMgr()
	: mAccTime(0.f)
	, mMaxTime(1.f)
	, mSpeed(0.f)
	, mWhiteCutton(nullptr)
	, mHitCutton(nullptr)
	, mCutton(nullptr)
{
}

void CameraMgr::Initialize()
{
	Vec2 resolution = APP_INSTANCE.GetResolution();
	mLookPos = resolution / 2.f;

	mCutton = ResourceMgr::GetInstance().CreateTexture(L"Cutton", Vec2(WINDOW_WIDTH_SIZE, WINDOW_HEIGHT_SIZE));

	mHitCutton = LOAD_TEXTURE(L"HitCutton", L"Texture\\RedWarningOnHit2.bmp");
	mWhiteCutton = LOAD_TEXTURE(L"WhiteCutton", L"Texture\\WhiteCutton.bmp");
	
	mBlendFunc = {};
	mBlendFunc.BlendFlags = 0;
	mBlendFunc.AlphaFormat = 0;
	mBlendFunc.BlendOp = AC_SRC_OVER;
	mBlendFunc.SourceConstantAlpha = 0;

	mCurEffect = {};
	mCurEffect.mEffect = CAMERA_EFFECT::END;

	mCamLimitRect.left = 0;
	mCamLimitRect.top = 0;
	mCamLimitRect.right = WINDOW_WIDTH_SIZE * 10;
	mCamLimitRect.bottom = WINDOW_HEIGHT_SIZE * 10;

	mBottomLimit = TILE_SIZE * 27;
}

void CameraMgr::Update()
{

	if (IS_PRESSED(KEY::UP))
		mLookPos.y -= (CAMERA_SPEED * DT);
	
	if (IS_PRESSED(KEY::DOWN))
		mLookPos.y += (CAMERA_SPEED * DT);
	
	if (IS_PRESSED(KEY::LEFT))
		mLookPos.x -= (CAMERA_SPEED * DT);
	
	if (IS_PRESSED(KEY::RIGHT))
		mLookPos.x += (CAMERA_SPEED * DT);

	WorldToScreenCalc();

	if (nullptr != mObject)
	{
		if (mObject->GetType() == OBJECT_TYPE::PLAYER)
		{
			Vec2 pos = mObject->GetPos();
			mPrevLookPos = mLookPos;
			mLookPos = pos;
		}
		else
		{
			mCurLookPos = mObject->GetPos();
		}

		if (mLookPos.x - WINDOW_WIDTH_SIZE / 2.f < 0.f)
			mLookPos.x = WINDOW_WIDTH_SIZE / 2.f;

		if (mLookPos.x + WINDOW_WIDTH_SIZE / 2.f > mCamLimitRect.right)
			mLookPos.x = mCamLimitRect.right - WINDOW_WIDTH_SIZE /2.f;

		if (mLookPos.y - WINDOW_HEIGHT_SIZE / 2.f < 0.f)
			mLookPos.y = WINDOW_HEIGHT_SIZE / 2.f;

		if (mLookPos.y + WINDOW_HEIGHT_SIZE / 2.f > mCamLimitRect.bottom)
			mLookPos.y = mCamLimitRect.bottom - WINDOW_HEIGHT_SIZE / 2.f;
	}

	if (mCamEffects.empty())
		return;

	CameraEffect& mCurEffect = mCamEffects.front();


	if (mCurEffect.mDelayTime > mCurEffect.mCurDelayTime)
	{
		mCurEffect.mCurDelayTime += DT;
		return;
	}

	mCurEffect.mAlphaTime += DT;
	float ratio = mCurEffect.mAlphaTime / mCurEffect.mEndTime;

	switch (mCurEffect.mEffect)
	{
	case CAMERA_EFFECT::FADE_IN_FROM_WHITE:
	case CAMERA_EFFECT::FADE_IN:
		mAlphaValue = 1.0f - ratio;
		mBlendFunc.SourceConstantAlpha = (BYTE)(255.f * mAlphaValue);
		break;

	case CAMERA_EFFECT::FADE_OUT:
		mAlphaValue = ratio;
		mBlendFunc.SourceConstantAlpha = (BYTE)(255.f * mAlphaValue);
		break;

	case CAMERA_EFFECT::SHAKE:
		mLookPos.x += 2.f;
		break;

	case CAMERA_EFFECT::BOSS_SHAKE:
		mLookPos.x += 5.f;

	case CAMERA_EFFECT::HIT:
		mAlphaValue = 1.0f - ratio;
		mBlendFunc.SourceConstantAlpha = (BYTE)(50 * mAlphaValue);
		break;
	}
	
	if (mCurEffect.mAlphaTime >= mCurEffect.mEndTime)
	{
		mCamEffects.pop_front();
		mAlphaValue = 0.0f;
	}
}

void CameraMgr::Render()
{
	if (mCamEffects.empty() || 
		CAMERA_EFFECT::SHAKE == mCamEffects.front().mEffect || 
		CAMERA_EFFECT::BOSS_SHAKE == mCamEffects.front().mEffect )
		return;

	CameraEffect& mCurEffect = mCamEffects.front();

	if (mCurEffect.mDelayTime > mCurEffect.mCurDelayTime)
	{
		return;
	}


	if (CAMERA_EFFECT::HIT == mCurEffect.mEffect)
	{
		mBlendFunc.AlphaFormat = AC_SRC_ALPHA;
		AlphaBlend(BACK_BUF_DC,
			0, 0,
			WINDOW_WIDTH_SIZE, WINDOW_HEIGHT_SIZE,
			mHitCutton->GetDC(),
			0, 0,
			mHitCutton->GetWidth(),
			mHitCutton->GetHeight(),
			mBlendFunc);
	}

	else
	{

		if (CAMERA_EFFECT::FADE_IN_FROM_WHITE == mCurEffect.mEffect)
		{
			mBlendFunc.AlphaFormat = 0;
			AlphaBlend(BACK_BUF_DC,
				0, 0,
				WINDOW_WIDTH_SIZE, WINDOW_HEIGHT_SIZE,
				mWhiteCutton->GetDC(),
				0, 0,
				mWhiteCutton->GetWidth(),
				mWhiteCutton->GetHeight(),
				mBlendFunc);
		}

		else
		{
			mBlendFunc.AlphaFormat = 0;
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

	
}

void CameraMgr::SetLookPos(Vec2 _pos)
{
	mLookPos = _pos;
	
	float distance = (mLookPos - mPrevLookPos).Len();
	mSpeed = distance / mMaxTime;
	mAccTime = 0.f;
}

Vec2 CameraMgr::GetTileCoord(Vec2 _tilePos) const
{
	Vec2 calVec = {};
	calVec.x = (float)(TILE_SIZE * (int)(_tilePos.x / TILE_SIZE));
	calVec.y = (float)(TILE_SIZE * (int)(_tilePos.y / TILE_SIZE));
	return calVec;
}

Vec2 CameraMgr::GetIconUIPos(Vec2 _uiPos, int _index) const
{
	int offset = _index * (TILE_SIZE * 3);
	return Vec2(_uiPos.x, _uiPos.y - offset);
}

bool CameraMgr::OutOfScreen(Vec2 _pos)
{
	Vec2 pos = GetRenderPos(_pos);
	if (pos.x < -100.f ||
		pos.y < -100.f ||
		pos.x > mCamLimitRect.right + 100.f || 
		pos.y > mCamLimitRect.bottom + 100.f)
		return true;

	return false;
}

void CameraMgr::WorldToScreenCalc()
{
	mAccTime += DT;

	if (mMaxTime <= mAccTime)
	{
		mCurLookPos = mLookPos;
	}

	else
	{
		Vec2 lookDir = mLookPos - mPrevLookPos;

		if (false == lookDir.IsZero())
		{
			lookDir.Norm();
			mCurLookPos = mPrevLookPos + (lookDir * mSpeed * DT);
		}
	}
	
	Vec2 resolution = APP_INSTANCE.GetResolution();
	Vec2 center = resolution / 2.f;

	mDistance = mCurLookPos - center;
	mPrevLookPos = mCurLookPos;
}

void CameraMgr::SetEffect(CAMERA_EFFECT _effect, float _endTime, float _delayTime)
{
	if (_endTime <= 0.0f)
		return;

	CameraEffect camEffect = {};
	camEffect.mEffect = _effect;
	camEffect.mEndTime = _endTime;
	camEffect.mAlphaTime = 0.0f;
	camEffect.mDelayTime = _delayTime;
	camEffect.mCurDelayTime = 0.0f;

	mCamEffects.push_back(camEffect);
}

void CameraMgr::RemoveEffect()
{
	mCamEffects.clear();
}
