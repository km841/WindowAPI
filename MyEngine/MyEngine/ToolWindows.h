#pragma once
#include "Singleton.h"

class Texture;
class ToolWindows :
	public Singleton< ToolWindows >
{

public:
	ToolWindows();
	~ToolWindows();

public:
	void Initialize();
	void Update();
	void Render();
	void Destroy();
	
public:
	void WindowInit();
	inline void DisableWindow() const {
		ShowWindow(mData.hWnd, SW_HIDE); 
		Resize(); 
	}
	inline void EnableWindow() const { 
		ShowWindow(mData.hWnd, SW_SHOW); 
		Resize();
	}

	inline void Resize() const { SetWindowPos(mData.hWnd, 0, WINDOW_WIDTH_SIZE, 0, mData.iWidth, APP_INSTANCE.GetHeight(), NULL); };
	
	void CreateButton(TOOL_ID _id, const std::wstring& _bmpPath, Vec2 _pos, Vec2 _size);
	ButtonInfo& GetButtonInfo(TOOL_ID _id) { return mBtnMap[_id]; }

	void AllButtonRelease();

	void ProcessClicked(TOOL_ID _id);

private:
	WindowData mData;
	std::wstring mWindowName;

	std::map<TOOL_ID, ButtonInfo> mBtnMap;

};

