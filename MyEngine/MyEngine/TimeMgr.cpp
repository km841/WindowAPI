#include "pch.h"
#include "TimeMgr.h"
#include "FontMgr.h"
#include "Texture.h"

void TimeMgr::Initialize()
{
	QueryPerformanceFrequency(&mPrequency);
	QueryPerformanceCounter(&mPrevCount);
}

void TimeMgr::Update()
{
	QueryPerformanceCounter(&mCurCount);
	mDT = (float)(mCurCount.QuadPart - mPrevCount.QuadPart) / (float)(mPrequency.QuadPart);
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
