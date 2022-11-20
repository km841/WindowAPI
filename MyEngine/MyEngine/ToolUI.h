#pragma once
#include "UI.h"

class Tile;
class ToolUI :
    public UI
{
public:
	ToolUI();
	~ToolUI();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	virtual bool OnMouse();
	virtual bool OnClicked();

public:
	inline void SetPage(int _page) { mCurPage = _page; }
	inline int  GetPage() const { return mCurPage; }

private:
	int mCurPage;
	
	// 카메라같은 개념을 도입해서 페이지에 따라 pos가 달라지게끔 함


};

