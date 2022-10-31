#include "pch.h"
#include "Application.h"

/*======<   Scene   >======*/
#include "SceneMgr.h"      //
#include "Scene.h"         //
/*=========================*/

#include "ResourceMgr.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "EventMgr.h"
#include "CollisionMgr.h"

void Application::Initialize(const WindowData& _winData)
{
	WindowInit(_winData);
	
	// 각종 매니저 초기화
	KeyMgr::GetInstance().Initialize();
	TimeMgr::GetInstance().Initialize();
	//ResourceMgr::GetInstance().Initialize();
	SceneMgr::GetInstance().Initialize();
	
}

void Application::WindowInit(const WindowData& _winData)
{
	mWinData = _winData;
	mWinData.hMainDC = GetDC(mWinData.hWnd);
	mWinData.hBackBufDC = CreateCompatibleDC(mWinData.hMainDC);
	mWinData.hBackBufBit = CreateCompatibleBitmap(mWinData.hMainDC, mWinData.iWidth, mWinData.iHeight);
	HBITMAP oldBit = (HBITMAP)SelectObject(mWinData.hBackBufDC, mWinData.hBackBufBit);
	DeleteObject(oldBit);

	RECT rect = { 0, 0, static_cast<LONG>(mWinData.iWidth), static_cast<LONG>(mWinData.iHeight) };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	SetWindowPos(mWinData.hWnd, NULL, 0, 0, mWinData.iWidth, mWinData.iHeight, NULL);
	mWinData.iWidth = rect.right;
	mWinData.iHeight = rect.bottom;
}

void Application::Tick()
{
	Rectangle(BACK_BUF_DC, 0, 0, GetWidth(), GetHeight());

	//Pen pen(BACK_BUF_DC, PEN_TYPE::BLUE);
	//Brush brush(BACK_BUF_DC, BRUSH_TYPE::GRAY);
	//Rectangle(BACK_BUF_DC, 100, 100, 300, 300);
	
	KeyMgr::GetInstance().Update();
	TimeMgr::GetInstance().Update();
	SceneMgr::GetInstance().Update();
	SceneMgr::GetInstance().Render();
	CollisionMgr::GetInstance().Update();
	TimeMgr::GetInstance().Render();

	



	//Double Buffering
	BitBlt(MAIN_DC, 0, 0, GetWidth(), GetHeight(), GetBackBufDC(), 0, 0, SRCCOPY);
	
	EventMgr::GetInstance().Update();
}

void Application::Render()
{


}

void Application::Destroy()
{
	ReleaseDC(mWinData.hWnd, mWinData.hMainDC);
	DeleteDC(mWinData.hBackBufDC);
	DeleteObject(mWinData.hBackBufBit);
}


