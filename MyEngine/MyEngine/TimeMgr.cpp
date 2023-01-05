

#include "pch.h"
#include "TimeMgr.h"
#include "FontMgr.h"
#include "Texture.h"
#include "MouseMgr.h"

TimeMgr::TimeMgr()
	: mPrevCount{}
	, mCurCount{}
	, mFrequency{}
	, mMagnification(1.f)
	, mSettingMaxTime(0.f)
	, mSettingCurTime(0.f)
	, mDT(0.f)
	, mAcc(0.)
	, mCallCount(0)
	, mFPS(0)
	, mDTChange(false)
	, mAccSec(0)
	, mCountTime(false)
{
}

TimeMgr::~TimeMgr()
{
}

void TimeMgr::Initialize()
{
	QueryPerformanceCounter(&mPrevCount);
	QueryPerformanceFrequency(&mFrequency);
}

void TimeMgr::Update()
{
	QueryPerformanceFrequency(&mFrequency);
	QueryPerformanceCounter(&mCurCount);

	mDT = (float)(mCurCount.QuadPart - mPrevCount.QuadPart) / (float)(mFrequency.QuadPart);
	mPrevCount = mCurCount;

	if (mDTChange)
	{
		if (mSettingMaxTime < mSettingCurTime)
		{
			mSettingCurTime = 0.f;
			mDTChange = false;
		}

		else
		{
			mSettingCurTime += mDT;
			mDT *= mMagnification;
		}
	}

	if (mDT > (1.f / 60.f))
		mDT = (1.f / 60.f);
}

void TimeMgr::Render()
{
	++mCallCount;

	mAcc += mDT;

	if (mAcc >= 1.)
	{
		mFPS = mCallCount;
		
		mAcc = 0.;
		mCallCount = 0;

		if (mCountTime)
			++mAccSec;

		wchar_t szBuffer[256] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", mFPS, mDT);
		SetWindowText(APP_INSTANCE.GetHwnd(), szBuffer);
		//wchar_t szBuffer[256] = {};
		//swprintf_s(szBuffer, L"mousePos : %f, %f", MOUSE_POS.x, MOUSE_POS.y);
		//SetWindowText(APP_INSTANCE.GetHwnd(), szBuffer);
	}
}

std::wstring TimeMgr::GetCurTime()
{
	time_t timer = time(NULL);
	tm* t = localtime(&timer);

	int year = t->tm_year + 1900;
	int month = t->tm_mon + 1;
	int day = t->tm_mday;
	int hour = t->tm_hour;
	int min = t->tm_min;
	int sec = t->tm_sec;

	wchar_t buff[COMMENT_MAX_SIZE] = {};
	swprintf_s(buff, L"%d-%d-%d_%d:%d:%d", year, month, day, hour, min, sec);

	return std::wstring(buff);
}

void TimeMgr::SetDeltaTime(float _magn, float _maxTime)
{
	mDTChange = true;
	mMagnification = _magn;
	mSettingMaxTime = _maxTime;
	mSettingCurTime = 0.f;
}
