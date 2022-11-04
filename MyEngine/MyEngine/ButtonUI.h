#pragma once
#include "UI.h"

struct TextureInfo
{
	Vec2 mLeftTop;
	Vec2 mOffset;
	Vec2 mSize;
};

enum class ButtonState
{
	MOUSE_ON,
	NONE,
	END,
};

class Texture;
class ButtonUI :
    public UI
{
public:
	ButtonUI();
	~ButtonUI();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	void TextureProcessing(Vec2 _leftTop, Vec2 _offset, Vec2 _size);


private:
	bool mOnMouse;
	TextureInfo mStates[(UINT)ButtonState::END];
};

