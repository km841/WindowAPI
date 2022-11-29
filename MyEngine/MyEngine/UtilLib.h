#pragma once
#include <Windows.h>

struct MonsterInfo
{
	int mHP;
	float mSpeed;
	float mRecog;
	float mAttRange;
};

struct WindowGDI
{
	static HPEN			hPens[(UINT)PEN_TYPE::END];
	static HBRUSH		hBrushes[(UINT)BRUSH_TYPE::END];

	WindowGDI()
	{
		// Pen Initialize
		hPens[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		hPens[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		hPens[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));

		// Brush Initialize
		hBrushes[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
		hBrushes[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);
		hBrushes[(UINT)BRUSH_TYPE::WHITE] = (HBRUSH)GetStockObject(WHITE_BRUSH);
		hBrushes[(UINT)BRUSH_TYPE::GRAY] = (HBRUSH)GetStockObject(GRAY_BRUSH);
		hBrushes[(UINT)BRUSH_TYPE::MAGENTA] = CreateSolidBrush(RGB(255, 0, 255));
	}

	~WindowGDI()
	{
		for (int i = 0; (UINT)PEN_TYPE::END > i; ++i)
			DeleteObject(hPens[i]);
		
		for (int i = 0; (UINT)BRUSH_TYPE::END > i; ++i)
			DeleteObject(hBrushes[i]);
	}
};

struct WindowData
{
	HINSTANCE	 hInst;
	HWND		 hWnd;
	UINT		 iWidth;
	UINT		 iHeight;
	
	HDC			 hMainDC;
	HDC			 hBackBufDC;
	HBITMAP		 hBackBufBit;
};

struct Pen
{
public:
	Pen(HDC _dc, PEN_TYPE _eType)
	{
		mDC = _dc;
		mOldPen = (HPEN)SelectObject(mDC, WindowGDI::hPens[(UINT)_eType]);
	}

	~Pen()
	{
		SelectObject(mDC, mOldPen);
	}

private:
	HDC mDC;
	HPEN mOldPen;
};

struct Brush
{
public:
	Brush(HDC _dc, BRUSH_TYPE _eType)
	{
		mDC = _dc;
		mOldBrush = (HBRUSH)SelectObject(mDC, WindowGDI::hBrushes[(UINT)_eType]);
	}

	~Brush()
	{
		SelectObject(mDC, mOldBrush);
	}

private:
	HDC mDC;
	HBRUSH mOldBrush;
};

struct Event
{
	EVENT_TYPE eType;
	DWORD_PTR lParam;
	DWORD_PTR wParam;
};

union Pixel
{
	struct
	{
		BYTE R;
		BYTE G;
		BYTE B;
		BYTE A;
	};
	DWORD Color;

	Pixel(BYTE r, BYTE g, BYTE b, BYTE a)
		:R(r), G(g), B(b), A(a)
	{}

	Pixel(COLORREF color)
		:Color(color)
	{}

	bool IsMagenta()
	{
		return (R == 255 && G == 0 && B == 255);
	}
	
	bool IsWhite()
	{
		return (R == 255 && G == 255 && B == 255);
	}

	bool IsBlue()
	{
		return (R == 0 && G == 0 && B == 255);
	}
};

