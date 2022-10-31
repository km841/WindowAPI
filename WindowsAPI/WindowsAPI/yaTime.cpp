#include "yaTime.h"


namespace ya
{
	LARGE_INTEGER Time::mCpuFrequency = {};
	LARGE_INTEGER Time::mPrevFrequency = {};
	LARGE_INTEGER Time::mCurFrequency = {};
	float Time::mDeltaTime = 0.f;

	void Time::Initialize()
	{
		// CPU �ʴ� �ݺ��Ǵ� ������ ����
		QueryPerformanceFrequency(&mCpuFrequency);
		// ���α׷� ���� �� CPU Ŭ�� ��
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