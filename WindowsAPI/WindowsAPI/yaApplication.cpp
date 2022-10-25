#include "yaApplication.h"
#include "yaSceneManager.h"
#include "yaTime.h"
#include "yaInput.h"
#include "Common.h"
#include "MeteorManager.h"




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
		MeteorManager::GetInstance().Initialize();
	}

	void Application::Tick()
	{
		Time::Tick();
		Input::Tick();

		Rectangle(mWindowData.backBuffer, -1, -1, mWindowData.width + 1, mWindowData.height + 1);
		SceneManager::Tick();
		MeteorManager::GetInstance().Tick();
		
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
		ReleaseDC(mWindowData.hWnd, mWindowData.hdc);
		
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
	}
}

