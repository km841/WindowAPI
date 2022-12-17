

#include "pch.h"
#include "TimeMgr.h"
#include "FontMgr.h"
#include "Texture.h"

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

		wchar_t szBuffer[256] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", mFPS, mDT);
		SetWindowText(APP_INSTANCE.GetHwnd(), szBuffer);
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
