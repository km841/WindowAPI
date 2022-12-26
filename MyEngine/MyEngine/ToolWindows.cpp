#include "pch.h"
#include "ToolWindows.h"
#include "ResourceMgr.h"
#include "MouseMgr.h"
#include "IconUI.h"
#include "FontMgr.h"
#include "Texture.h"

LRESULT CALLBACK WndProc_Tool(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

ToolWindows::ToolWindows()
	: mMonsterTex(nullptr)
	, mCurID(TOOL_ID::END)
	
{
	mWindowName = L"ToolWindows";
	mData.iWidth = 300;
	mData.iHeight = APP_INSTANCE.GetHeight();
	mData.hInst = APP_INSTANCE.GetHandleInstance();

	mNormalFont = CreateFont(20, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, _T("Consolas"));
	mSemiBoldFont = CreateFont(20, 0, 0, 0, FW_SEMIBOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, _T("Consolas"));
	mBoldFont = CreateFont(20, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, _T("Consolas"));
}

ToolWindows::~ToolWindows()
{
}

void ToolWindows::Initialize()
{
	WindowInit();

	CreateText(L"■ 몬스터 선택", Vec2(75, 10), Vec2(120, 20), FONT_TYPE::SEMI_BOLD);
	CreateButton(TOOL_ID::BTN_RED_GIANT_BAT, L"..\\Resource\\Texture\\Btn_RedGiantBat.bmp", Vec2(24, 60), Vec2(64, 64));
	CreateButton(TOOL_ID::BTN_GIANT_BAT, L"..\\Resource\\Texture\\Btn_GiantBat.bmp", Vec2(108, 60), Vec2(64, 64));
	CreateButton(TOOL_ID::BTN_MINOTAUR, L"..\\Resource\\Texture\\Btn_Minotaur.bmp", Vec2(192, 60), Vec2(64, 64));
	CreateButton(TOOL_ID::BTN_ICE_MAGE, L"..\\Resource\\Texture\\Btn_IceMage.bmp", Vec2(24, 144), Vec2(64, 64));
	CreateButton(TOOL_ID::BTN_BANSHEE, L"..\\Resource\\Texture\\Btn_Banshee.bmp", Vec2(108, 144), Vec2(64, 64));
	CreateButton(TOOL_ID::BTN_ICE_GRAY_SKULL, L"..\\Resource\\Texture\\Btn_GrayIceSkull.bmp", Vec2(192, 144), Vec2(64, 64));
	CreateButton(TOOL_ID::BTN_GIANT_SKULL, L"..\\Resource\\Texture\\Btn_GiantSkull.bmp", Vec2(24, 228), Vec2(64, 64));
	CreateButton(TOOL_ID::BTN_OVIBOS, L"..\\Resource\\Texture\\Btn_Ovibos.bmp", Vec2(108, 228), Vec2(64, 64));

	CreateText(L"■ 던전 오브젝트 선택", Vec2(15, 370), Vec2(240, 20), FONT_TYPE::SEMI_BOLD);
	CreateButton(TOOL_ID::BTN_DOOR_0DEG, L"..\\Resource\\Texture\\Btn_LockedDoor_0Deg.bmp", Vec2(24, 420), Vec2(64, 64));
	CreateButton(TOOL_ID::BTN_DOOR_90DEG, L"..\\Resource\\Texture\\Btn_LockedDoor_900Deg.bmp", Vec2(108, 420), Vec2(64, 64));
	CreateButton(TOOL_ID::BTN_DOOR_270DEG, L"..\\Resource\\Texture\\Btn_LockedDoor_270Deg.bmp", Vec2(192, 420), Vec2(64, 64));
	CreateButton(TOOL_ID::BTN_DOOR_180DEG, L"..\\Resource\\Texture\\Btn_LockedDoor_0Deg.bmp", Vec2(24, 504), Vec2(64, 64));

	CreateText(L"> 다음 타일 페이지 (Page Up)", Vec2(15, 650), Vec2(240, 20), FONT_TYPE::NORMAL, false);
	CreateText(L"> 이전 타일 페이지 (Page Down)", Vec2(15, 670), Vec2(300, 20), FONT_TYPE::NORMAL, false);
	CreateText(L"> 선택 해제 (우클릭)", Vec2(15, 690), Vec2(240, 20), FONT_TYPE::NORMAL, false);
	CreateText(L"> 맵 저장하기 (CTRL + S)", Vec2(15, 710), Vec2(240, 20), FONT_TYPE::NORMAL, false);
	CreateText(L"> 맵 불러오기 (CTRL + O)", Vec2(15, 730), Vec2(240, 20), FONT_TYPE::NORMAL, false);
}

void ToolWindows::Update()
{
}

void ToolWindows::Render()
{
}

void ToolWindows::Destroy()
{
	ReleaseDC(mData.hWnd, mData.hMainDC);
	DeleteDC(mData.hBackBufDC);
	DeleteObject(mData.hBackBufBit);

	for (auto& info : mBtnMap)
	{
		DeleteObject(info.second.mBitmap);
	}
}

void ToolWindows::WindowInit()
{
	mData.hMainDC = GetDC(mData.hWnd);
	mData.hBackBufDC = CreateCompatibleDC(mData.hMainDC);
	mData.hBackBufBit = CreateCompatibleBitmap(mData.hMainDC, mData.iWidth, mData.iHeight);
	HBITMAP oldBit = (HBITMAP)SelectObject(mData.hBackBufDC, mData.hBackBufBit);
	DeleteObject(oldBit);

	WNDCLASSEX wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc_Tool;
	wcex.hInstance = mData.hInst;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(240, 240, 240)));
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = mWindowName.c_str();

	RegisterClassEx(&wcex);

	mData.hWnd = CreateWindowEx(0,
		mWindowName.c_str(),
		mWindowName.c_str(),
		WS_OVERLAPPED,
		WINDOW_WIDTH_SIZE, 0,
		mData.iWidth,
		mData.iHeight,
		NULL,
		NULL,
		APP_INSTANCE.GetHandleInstance(),
		NULL
	);
}

void ToolWindows::CreateButton(TOOL_ID _id, const std::wstring& _bmpPath, Vec2 _pos, Vec2 _size)
{
	ButtonInfo info = {};
	info.mHwnd = CreateWindowEx(
		0, L"button", L"button"
		, WS_VISIBLE | WS_CHILD | BS_BITMAP | BS_NOTIFY
		, (int)_pos.x
		, (int)_pos.y
		, (int)_size.x
		, (int)_size.y, 
		mData.hWnd, 
		(HMENU)_id, 
		mData.hInst, 
		NULL
	);

	info.mBitmap = (HBITMAP)LoadImage(NULL, _bmpPath.c_str(), IMAGE_BITMAP,
		0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	SendMessage(info.mHwnd, BM_SETIMAGE, 0, (LPARAM)info.mBitmap);
	mBtnMap.insert(std::make_pair(_id, info));
}

void ToolWindows::CreateText(const std::wstring& _text, Vec2 _pos, Vec2 _size, FONT_TYPE _fontType, bool _centerAlign)
{
	UINT style = WS_VISIBLE | WS_CHILD | SS_CENTER;

	if (false == _centerAlign)
	{
		style = WS_VISIBLE | WS_CHILD;
	}

	HWND hwnd = CreateWindowEx(
		0, L"static", _text.c_str()
		, style
		, (int)_pos.x
		, (int)_pos.y
		, (int)_size.x
		, (int)_size.y,
		mData.hWnd,
		(HMENU)-1,
		mData.hInst,
		NULL
	);

	switch (_fontType)
	{
	case FONT_TYPE::NORMAL:
		SendMessage(hwnd, WM_SETFONT, (WPARAM)(mNormalFont), 0);
		break;
	case FONT_TYPE::SEMI_BOLD:
		SendMessage(hwnd, WM_SETFONT, (WPARAM)(mSemiBoldFont), 0);
		break;
	case FONT_TYPE::BOLD:
		SendMessage(hwnd, WM_SETFONT, (WPARAM)(mBoldFont), 0);
		break;
	}
	
}

TOOL_ID ToolWindows::GetSelectedID() const
{
	for (auto& info : mBtnMap)
	{
		if (info.second.mState)
			return info.first;
	}

	return TOOL_ID::END;
}

void ToolWindows::AllButtonRelease()
{
	for (auto& info : mBtnMap)
	{
		info.second.mState = false;
		Button_SetState(info.second.mHwnd, false);
	}
}

void ToolWindows::ProcessClicked(TOOL_ID _id)
{
	IconUI::ClearSelectedUI();
	ButtonInfo& info = GetButtonInfo(_id);
	if (IS_LBUTTON_CLICKED)
	{
		if (true == info.mState)
		{
			Button_SetState(info.mHwnd, FALSE);
			info.mState = false;
		}

		else
		{
			TOOL_INSTANCE.AllButtonRelease();
			Button_SetState(info.mHwnd, TRUE);
			info.mState = true;
		}
	}
}



LRESULT WndProc_Tool(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		break;

	case WM_PAINT:
		break;

	case WM_COMMAND:
		TOOL_INSTANCE.ProcessClicked((TOOL_ID)LOWORD(wParam));
		break;

	case WM_QUIT:
		PostQuitMessage(0);
		break;


	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}