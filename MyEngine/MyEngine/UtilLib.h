#pragma once
#include <Windows.h>

struct ItemInfo
{
	ItemInfo()
		: mAtt(0.f)
		, mAttSpeed(0.f)
		, mAmmo(0.f)
		, mMaxAmmo(0.f)
	{}
	std::wstring mItemName;
	std::wstring mItemComment;
	float mAtt;
	float mAttSpeed;
	float mAmmo;
	float mMaxAmmo;
	RARITY mRarity;
	WEAPON_TYPE mWeaponType;

	//Stat
};

struct BulletInfo
{
	BulletInfo()
		: mSpeed(0.f)
		, mAtt(0.f)
	{}

	BulletInfo(float _att, float _speed)
		: mSpeed(_speed)
		, mAtt(_att)
	{}
	float mSpeed;
	float mAtt;
};

struct MonsterInfo
{
	MonsterInfo()
		: mAtt(0.f)
		, mMaxHP(0.f)
		, mCurHP(0.f)
		, mSpeed(0.f)
		, mRecog(0.f)
		, mAttRange(0.f)
		, mAttDelay(0.f)
		, mCurDelay(0.f)
		, mAttFinFlag(false)
	{}
	float mAtt;
	float mMaxHP;
	float mCurHP;
	float mSpeed;
	float mRecog;
	float mAttRange;
	float mAttDelay;
	float mCurDelay;
	bool mAttFinFlag;
};

struct PlayerInfo
{
	PlayerInfo()
		:mMaxHP(0.f)
		,mCurHP(0.f)
		,mAtt(0.f)
		,mDashCount(0.f)
		,mSpeed(0.f)
	{}
	float mMaxHP;
	float mCurHP;
	float mAtt;
	float mDashCount;
	float mSpeed;
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
		hPens[(UINT)PEN_TYPE::WHITE] = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
		hPens[(UINT)PEN_TYPE::GRAY] = CreatePen(PS_SOLID, 2, RGB(147, 144, 158));
		hPens[(UINT)PEN_TYPE::BLACK] = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		hPens[(UINT)PEN_TYPE::NULL_COLOR] = (HPEN)GetStockObject(NULL_PEN);

		// Brush Initialize
		hBrushes[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
		hBrushes[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);
		hBrushes[(UINT)BRUSH_TYPE::WHITE] = (HBRUSH)GetStockObject(WHITE_BRUSH);
		hBrushes[(UINT)BRUSH_TYPE::GRAY] = (HBRUSH)GetStockObject(GRAY_BRUSH);
		hBrushes[(UINT)BRUSH_TYPE::MAGENTA] = CreateSolidBrush(RGB(255, 0, 255));
		hBrushes[(UINT)BRUSH_TYPE::BLUE] = CreateSolidBrush(RGB(0, 0, 255));
		hBrushes[(UINT)BRUSH_TYPE::RED] = CreateSolidBrush(RGB(255, 0, 0));
		hBrushes[(UINT)BRUSH_TYPE::GREEN] = CreateSolidBrush(RGB(0, 255, 0));
		hBrushes[(UINT)BRUSH_TYPE::YELLOW] = CreateSolidBrush(RGB(223, 233, 85));
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

	HMENU		 hMainMemu;
	HMENU		 hColMenu;
	HMENU		 hTypeMenu;
	wchar_t      szFileAddr[512];
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

	operator COLORREF()
	{
		return RGB(R, G, B);
	}

	Pixel(BYTE r, BYTE g, BYTE b, BYTE a)
		:R(r), G(g), B(b), A(a)
	{}

	Pixel(COLORREF color)
		:Color(color)
	{}

	bool operator==(const Pixel& _other)
	{
		return (R == _other.R) && (G == _other.G) && (B == _other.B);
	}

	bool operator!=(const Pixel& _other)
	{
		return !(*this == _other);
	}

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