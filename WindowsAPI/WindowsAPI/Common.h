#pragma once
#include "framework.h"
#include <string>
#include <vector>
#include <list>
#include <map>
#include <random>

#include "def.h"
#include "Maths.h"

//using Pos = POINT;

struct WindowData
{
	HWND hWnd;
	HDC hdc;
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
