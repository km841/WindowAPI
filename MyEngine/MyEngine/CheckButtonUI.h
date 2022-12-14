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
	static CheckButtonUI* GetCheckedButton() { return Checked; }
	static void SetCheckedButton(CheckButtonUI* _button) { Checked = _button; }

private:

	static CheckButtonUI* Checked;
	int  mIndex;
	CHECK_TYPE mCheckType;

};

