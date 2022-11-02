#include "pch.h"
#include "CameraMgr.h"
#include "TimeMgr.h"
#include "GameObject.h"
#include "KeyMgr.h"

void CameraMgr::Initialize()
{
	Vec2 resolution = APP_INSTANCE.GetResolution();
	mLookPos = resolution / 2.f;
}

void CameraMgr::Update()
{
	if (nullptr != mObject)
		mLookPos = mObject->GetPos();

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

void CameraMgr::WorldToScreenCalc()
{
	mAccTime += DT;

	Vec2 resolution = APP_INSTANCE.GetResolution();
	Vec2 center = resolution / 2.f;
	mDistance = mLookPos - center;
}
