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
	
	// ī�޶��� ������ �����ؼ� �������� ���� pos�� �޶����Բ� ��


};

