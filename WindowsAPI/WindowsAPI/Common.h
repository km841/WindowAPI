#pragma once
#include "framework.h"
#include <string>
#include <vector>
#include <list>
#include <map>
#include <random>
#include <bitset>
#include <set>

#include "def.h"
#include "Maths.h"

#pragma comment(lib, "Msimg32.lib")

//using Pos = POINT;

struct WindowData
{
	HWND hWnd;
	HDC hdc;

	HBITMAP backTexture;
	HDC backBuffer;

	UINT height;
	UINT width;


	void clear()
	{
		HWND hWnd = nullptr;
		HDC hdc = nullptr;
		UINT height = 0;
		UINT width = 0;
	}
};

struct Pen
{
	Pen(HDC hdc)
		: mHdc(hdc)
		, mOldPen(NULL)
		, mPen(NULL)
	{

	}

	Pen(HDC hdc, HPEN pen)
		: mHdc(hdc)
		, mOldPen(NULL)
		, mPen(pen)
	{
		mOldPen = (HPEN)SelectObject(mHdc, pen);
	};

	~Pen()
	{
		SelectObject(mHdc, mOldPen);
		DeleteObject(mPen);
	};

	void SetPen(HPEN pen)
	{
		mOldPen = (HPEN)SelectObject(mHdc, pen);
	}



private:
	HDC mHdc;
	HPEN mOldPen;
	HPEN mPen;
};


struct Brush
{
	Brush(HDC hdc, HBRUSH brush) 
	: mHdc(hdc)
	, mOldBrush(NULL)
	, mBrush(brush)
	{
		mOldBrush = (HBRUSH)SelectObject(mHdc, brush);
	};

	~Brush() 
	{
		SelectObject(mHdc, mOldBrush);
		DeleteObject(mBrush);
	};


private:
	HDC mHdc;
	HBRUSH mOldBrush;
	HBRUSH mBrush;
};