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
#include "SoundMgr.h"
#include "ToolWindows.h"


void Application::Initialize(const WindowData& _winData)
{
	WindowInit(_winData);
	//mFST.open(L"..\\Resource\\Log\\log.txt", std::ios::out | std::ios::app);

	// Manager Initialize
	if (FALSE == SoundMgr::GetInstance().Initialize())
		assert(nullptr);

	ToolWindows::GetInstance().Initialize();

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

	mWinData.hMainMemu = CreateMenu();
	HMENU hParentMenu = CreateMenu();
	mWinData.hColMenu = CreateMenu();
	mWinData.hTypeMenu = CreateMenu();

	AppendMenu(mWinData.hMainMemu, MF_POPUP, (UINT_PTR)hParentMenu, L"툴 옵션");

	AppendMenu(hParentMenu, MF_POPUP, (UINT_PTR)mWinData.hColMenu, L"타일 충돌 옵션");
	AppendMenu(mWinData.hColMenu,	MFT_RADIOCHECK, (UINT_PTR)ID::WALL, L"Wall (사각 충돌체)");
	AppendMenu(mWinData.hColMenu, MFT_RADIOCHECK, (UINT_PTR)ID::FOOTHOLD, L"Foothold (라인 충돌체)");
	AppendMenu(mWinData.hColMenu, MFT_RADIOCHECK, (UINT_PTR)ID::EMPTY, L"None (충돌체 없음)");

	AppendMenu(hParentMenu, MF_POPUP, (UINT_PTR)mWinData.hTypeMenu, L"타일 타입");
	AppendMenu(mWinData.hTypeMenu, MFT_RADIOCHECK, (UINT_PTR)ID::BACKGROUND, L"배경 타일");
	AppendMenu(mWinData.hTypeMenu, MFT_RADIOCHECK, (UINT_PTR)ID::SURFACE, L"표면 타일");

	_wgetcwd(mWinData.szFileAddr, FILENAME_MAX_SIZE);

	//SetMenu(mWinData.hWnd, mWinData.hMainMemu);
	CheckMenuRadioItem(mWinData.hColMenu, 0, 2, 2, MF_BYPOSITION);
	CheckMenuRadioItem(mWinData.hTypeMenu, 0, 1, 0, MF_BYPOSITION);

	SetWindowSize(false);
	srand(static_cast<UINT>(time(nullptr)));

	
}

void Application::SetWindowSize(bool _isMenu)
{
	RECT rect = { 0, 0, static_cast<LONG>(mWinData.iWidth), static_cast<LONG>(mWinData.iHeight) };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, _isMenu);
	SetWindowPos(mWinData.hWnd, NULL, 0, 0, rect.right, rect.bottom, NULL);

	RECT clientRect = {};
	GetClientRect(mWinData.hWnd, &clientRect);

	UINT rightDiff = WINDOW_WIDTH_SIZE - clientRect.right;
	UINT bottomDiff = WINDOW_HEIGHT_SIZE - clientRect.bottom;

	rect.right += rightDiff;
	rect.bottom += bottomDiff;

	SetWindowPos(mWinData.hWnd, NULL, 0, 0, rect.right, rect.bottom, NULL);

	mWinData.iWidth = rect.right;
	mWinData.iHeight = rect.bottom;
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

void Application::WriteLog(const std::wstring& _comment)
{
	const std::wstring& curTime = TimeMgr::GetInstance().GetCurTime();
	mFST << curTime << L" : " << _comment << L"\n";
}

void Application::Tick()
{
	// Mouse inside the screen
	//ConfineMouse();

	// Buffer Initialize
	Rectangle(BACK_BUF_DC, 0, 0, GetWidth(), GetHeight());

	// Manager Update
	
	TimeMgr::GetInstance().Update();
	KeyMgr::GetInstance().Update();
	MouseMgr::GetInstance().Update();
	SceneMgr::GetInstance().Update();
	UIMgr::GetInstance().Update();
	CameraMgr::GetInstance().Update();
	CollisionMgr::GetInstance().Update();
	FontMgr::GetInstance().Update();

	// Manager Render
	ToolWindows::GetInstance().Render();
	TimeMgr::GetInstance().Render();
	SceneMgr::GetInstance().Render();
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
	//mFST.close();
	ToolWindows::GetInstance().Destroy();
	FontMgr::GetInstance().Destroy();
	SceneMgr::GetInstance().Destroy();
	EventMgr::GetInstance().Destroy();
	UIMgr::GetInstance().Destroy();
	ClipCursor(NULL);
	ReleaseDC(mWinData.hWnd, mWinData.hMainDC);
	DeleteDC(mWinData.hBackBufDC);
	DeleteObject(mWinData.hBackBufBit);
}


