#pragma once
#include "ButtonUI.h"

class CheckButtonUI :
    public ButtonUI
{
public:
	CheckButtonUI();
	~CheckButtonUI();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	inline void SetIndex(int _index) { mIndex = _index; }
	inline int  GetIndex() const { return mIndex; }

	virtual void TextureProcessing(Vec2 _leftTop, Vec2 _offset, Vec2 _size);

public:
	virtual bool OnMouse();
	virtual bool OnClicked();

public:
	inline void SetCheckType(CHECK_TYPE _checkType) { mCheckType = _checkType; }
	inline CHECK_TYPE GetCheckType() const { return mCheckType; }


public:
	static CheckButtonUI* GetColTypeCheck() { return Checked_ColType; }
	static void           SetColTypeCheck(CheckButtonUI* _colTypeCheck) { Checked_ColType = _colTypeCheck; }

	static CheckButtonUI* GetTileTypeCheck() { return Checked_TileType; }
	static void           SetTileTypeCheck(CheckButtonUI* _tileTypeCheck) { Checked_TileType = _tileTypeCheck; }

	

private:
	static CheckButtonUI* Checked_ColType;
	static CheckButtonUI* Checked_TileType;
	int  mIndex;

	CHECK_TYPE mCheckType;

};

