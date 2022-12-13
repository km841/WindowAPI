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
	void ConfineMouse();

public:
	inline HDC GetMainDC() const { return mWinData.hMainDC; }
	inline HDC GetBackBufDC() const { return mWinData.hBackBufDC; }
	inline UINT GetWidth() const { return mWinData.iWidth; }
	inline UINT GetHeight() const { return mWinData.iHeight; }
	inline Vec2 GetResolution() const { return Vec2((float)(mWinData.iWidth), (float)(mWinData.iHeight)); }
	inline HWND GetHwnd() const { return mWinData.hWnd; }
	inline HMENU GetMainMenuHandle() const { return mWinData.hMainMemu; }
	inline HMENU GetColMenuHandle() const { return mWinData.hColMenu; }
	inline HMENU GetTypeMenuHandle() const { return mWinData.hTypeMenu; }

private:
	WindowData mWinData;
	WindowGDI  mWinGDI;

};

