#include "yaTime.h"


namespace ya
{
	LARGE_INTEGER Time::mCpuFrequency = {};
	LARGE_INTEGER Time::mPrevFrequency = {};
	LARGE_INTEGER Time::mCurFrequency = {};
	float Time::mDeltaTime = 0.f;

	void Time::Initialize()
	{
		// CPU 초당 반복되는 진동수 얻어옴
		QueryPerformanceFrequency(&mCpuFrequency);
		// 프로그램 시작 시 CPU 클럭 수
		QueryPerformanceCounter(&mPrevFrequency);
	}

	void Time::Tick()
	{
		QueryPerformanceCounter(&mCurFrequency);

		float differenceFrequency =
			static_cast<float>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart);

		mDeltaTime = differenceFrequency / static_cast<float>(mCpuFrequency.QuadPart);
		mPrevFrequency = mCurFrequency;
	}

	void Time::Render(HDC hdc)
	{
		//wchar_t szFloat[50] = {};
		//float fps = 1.0f / mDeltaTime;

		//swprintf_s(szFloat, 50, L"FPS : %f", fps);
		//int strLen = wcsnlen_s(szFloat, 50);

		//TextOut(hdc, 10, 10, szFloat, strLen);
	}

}