#pragma once
#include "Singleton.h"

class Application 
	: public Singleton< Application >
{
public:
	void Initialize(const WindowData& _winData);
	void Tick();
	void Render();
	void Destroy();

public:
	void WindowInit(const WindowData& _winData);

public:
	inline HDC GetMainDC() const { return mWinData.hMainDC; }
	inline HDC GetBackBufDC() const { return mWinData.hBackBufDC; }
	inline UINT GetWidth() const { return mWinData.iWidth; }
	inline UINT GetHeight() const { return mWinData.iHeight; }
	inline HWND GetHwnd() const { return mWinData.hWnd; }

private:
	WindowData mWinData;
	WindowGDI mWinGDI;

};

