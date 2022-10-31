#include "yaApplication.h"
#include "yaSceneManager.h"
#include "yaTime.h"
#include "yaInput.h"
#include "Common.h"
#include "yaResources.h"
#include "yaCollisionManager.h"
//#include "MeteorManager.h"




namespace ya
{
	
	Scene* SceneManager::mScenes[(UINT)eSceneType::Max] = {};
	Scene* SceneManager::mPlayScene = nullptr;
	void Application::Initialize(WindowData data)
	{
		InitializeWindow(data);


		Time::Initialize();
		Input::Initialize();
		SceneManager::Initialize();
		//MeteorManager::GetInstance().Initialize();
	}

	void Application::Tick()
	{
		Time::Tick();
		Input::Tick();
		SceneManager::Tick();

		CollisionManager::Tick();
		HBRUSH gray = (HBRUSH)GetStockObject(GRAY_BRUSH);
		Brush brush(mWindowData.backBuffer, gray);

		Rectangle(mWindowData.backBuffer, -1, -1, mWindowData.width + 1, mWindowData.height + 1);
		
		//MeteorManager::GetInstance().Tick();
		
		SceneManager::Render(mWindowData.backBuffer);
		Time::Render(mWindowData.backBuffer);
		Input::Render(mWindowData.backBuffer);
		
		BitBlt(mWindowData.hdc, 0, 0, mWindowData.width, mWindowData.height, mWindowData.backBuffer, 0, 0, SRCCOPY);
	}

	Application::Application()
	{
		mWindowData.clear();
	}

	Application::~Application()
	{
		SceneManager::Release();
		Resources::Release();

		ReleaseDC(mWindowData.hWnd, mWindowData.hdc);
		ReleaseDC(mWindowData.hWnd, mWindowData.backBuffer);

		for (int i = 0; i < (UINT)ePenColor::End; ++i)
		{
			DeleteObject(mPens[i]);
		}

		for (int i = 0; i < (UINT)eBrushColor::End; ++i)
		{
			DeleteObject(mBrushes[i]);
		}
		
		
	}
	void Application::InitializeWindow(WindowData data)
	{
		mWindowData = data;
		mWindowData.hdc = GetDC(data.hWnd);


		// 비트맵 해상도를 설정하기 위한 실제 윈도우 크기 계산
		RECT rect = { 0, 0, mWindowData.width, mWindowData.height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		SetWindowPos(
			mWindowData.hWnd
			, nullptr
			, 0
			, 0
			, rect.right - rect.left
			, rect.bottom - rect.top
			, 0);

		ShowWindow(mWindowData.hWnd, SW_SHOW);

		mWindowData.backTexture = CreateCompatibleBitmap(mWindowData.hdc, mWindowData.width, mWindowData.height);
		mWindowData.backBuffer = CreateCompatibleDC(mWindowData.hdc);
		HBITMAP defaultBitmap = (HBITMAP)SelectObject(mWindowData.backBuffer, mWindowData.backTexture);

		DeleteObject(defaultBitmap);

		// 메모리 해제 해주어야 함
		mPens[(UINT)ePenColor::Red] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		mPens[(UINT)ePenColor::Green] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		mPens[(UINT)ePenColor::Blue] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

		mBrushes[(UINT)eBrushColor::Transparent] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
		mBrushes[(UINT)eBrushColor::Black] = (HBRUSH)GetStockObject(BLACK_BRUSH);
		mBrushes[(UINT)eBrushColor::Gray] = CreateSolidBrush(RGB(71, 71, 71));
		mBrushes[(UINT)eBrushColor::White] = (HBRUSH)GetStockObject(WHITE_BRUSH);
	}
}

