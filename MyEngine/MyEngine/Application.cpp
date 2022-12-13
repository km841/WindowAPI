#include "pch.h"
#include "Application.h"

/*======<   Scene   >======*/
#include "SceneMgr.h"      //
#include "Scene.h"         //
/*=========================*/

#include "ResourceMgr.h"
#include "KeyMgr.h"
#include "MouseMgr.h"
#include "TimeMgr.h"
#include "EventMgr.h"
#include "CollisionMgr.h"
#include "CameraMgr.h"
#include "UIMgr.h"
#include "FontMgr.h"

void Application::Initialize(const WindowData& _winData)
{
	WindowInit(_winData);
	
	// Manager Initialize
	KeyMgr::GetInstance().Initialize();
	TimeMgr::GetInstance().Initialize();
	CameraMgr::GetInstance().Initialize();
	SceneMgr::GetInstance().Initialize();
	UIMgr::GetInstance().Initialize();
	FontMgr::GetInstance().Initialize();
	
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

	mWinData.hMainMemu = CreateMenu();
	HMENU hParentMenu = CreateMenu();
	mWinData.hColMenu = CreateMenu();
	mWinData.hTypeMenu = CreateMenu();

	AppendMenu(mWinData.hMainMemu, MF_POPUP, (UINT_PTR)hParentMenu, L"Tool Option");

	AppendMenu(hParentMenu, MF_POPUP, (UINT_PTR)mWinData.hColMenu, L"Tile Collision");
	AppendMenu(mWinData.hColMenu,	MFT_RADIOCHECK, (UINT_PTR)ID::WALL, L"Wall");
	AppendMenu(mWinData.hColMenu, MFT_RADIOCHECK, (UINT_PTR)ID::FOOTHOLD, L"Foothold");
	AppendMenu(mWinData.hColMenu, MFT_RADIOCHECK, (UINT_PTR)ID::EMPTY, L"Empty");

	AppendMenu(hParentMenu, MF_POPUP, (UINT_PTR)mWinData.hTypeMenu, L"Tile Type");
	AppendMenu(mWinData.hTypeMenu, MFT_RADIOCHECK, (UINT_PTR)ID::BACKGROUND, L"Background");
	AppendMenu(mWinData.hTypeMenu, MFT_RADIOCHECK, (UINT_PTR)ID::SURFACE, L"Surface");

	//SetMenu(mWinData.hWnd, mWinData.hMainMemu);
	CheckMenuRadioItem(mWinData.hColMenu, 0, 2, 2, MF_BYPOSITION);
	CheckMenuRadioItem(mWinData.hTypeMenu, 0, 1, 0, MF_BYPOSITION);


	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(mWinData.hWnd, NULL, 0, 0, rect.right, rect.bottom, NULL);

	RECT clientRect = {};
	GetClientRect(_winData.hWnd, &clientRect);

	UINT rightDiff = WINDOW_WIDTH_SIZE - clientRect.right;
	UINT bottomDiff = WINDOW_HEIGHT_SIZE - clientRect.bottom;

	rect.right += rightDiff;
	rect.bottom += bottomDiff;

	SetWindowPos(mWinData.hWnd, NULL, 0, 0, rect.right, rect.bottom, NULL);

	mWinData.iWidth = rect.right;
	mWinData.iHeight = rect.bottom;




	srand(static_cast<UINT>(time(nullptr)));
}

void Application::ConfineMouse()
{
	RECT rect = {};
	GetClientRect(GetHwnd(), &rect);

	POINT lt = {};
	POINT rb = {};
	lt.x = rect.left;
	lt.y = rect.top;
	rb.x = rect.right;
	rb.y = rect.bottom;

	ClientToScreen(GetHwnd(), &lt);
	ClientToScreen(GetHwnd(), &rb);
	rect.left = lt.x;
	rect.top = lt.y;
	rect.right = rb.x;
	rect.bottom = rb.y;
	ClipCursor(&rect);
}

void Application::Tick()
{
	// Mouse inside the screen
	// ConfineMouse();

	// Buffer Initialize
	Rectangle(BACK_BUF_DC, 0, 0, GetWidth(), GetHeight());

	// Manager Update
	KeyMgr::GetInstance().Update();
	MouseMgr::GetInstance().Update();
	TimeMgr::GetInstance().Update();
	SceneMgr::GetInstance().Update();
	UIMgr::GetInstance().Update();
	CameraMgr::GetInstance().Update();
	CollisionMgr::GetInstance().Update();
	FontMgr::GetInstance().Update();

	// Manager Render
	SceneMgr::GetInstance().Render();
	TimeMgr::GetInstance().Render();
	CameraMgr::GetInstance().Render();
	CollisionMgr::GetInstance().Render();
	FontMgr::GetInstance().Render();

	// Double Buffering
	BitBlt(MAIN_DC, 0, 0, GetWidth(), GetHeight(), BACK_BUF_DC, 0, 0, SRCCOPY);
	
	// Event Processing
	EventMgr::GetInstance().Update();
}

void Application::Render()
{

}

void Application::Destroy()
{
	FontMgr::GetInstance().Destroy();
	SceneMgr::GetInstance().Destroy();
	EventMgr::GetInstance().Destroy();
	UIMgr::GetInstance().Destroy();
	ClipCursor(NULL);
	ReleaseDC(mWinData.hWnd, mWinData.hMainDC);
	DeleteDC(mWinData.hBackBufDC);
	DeleteObject(mWinData.hBackBufBit);
}


