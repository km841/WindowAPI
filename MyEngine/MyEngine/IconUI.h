#pragma once
#include "UI.h"
class IconUI :
    public UI
{
public:
	IconUI();
	~IconUI();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	inline void SetLTPos(Vec2 _lt) { mLT = _lt; }
	inline Vec2 GetLTPos() const { return mLT; }

public:
	inline static IconUI* GetSelectedUI() { return selectedUI; }

private:
	Vec2 mLT;
	bool mClicked;
	
private:
	static IconUI* selectedUI;
};

