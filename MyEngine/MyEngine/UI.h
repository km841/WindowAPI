#pragma once
#include "GameObject.h"

class Texture;
class UI
	: public GameObject
{
public:
	UI(bool _camMode);
	virtual ~UI();

	UI(const UI& _other);

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	inline void SetTexture(Texture* _tex) { mTexture = _tex; }
	inline Texture* GetTexture() const { return mTexture; }

	inline void SetParentUI(UI* _parent) { mParentUI = _parent;}
	inline UI* GetParentUI() const { return mParentUI; }

	inline void AddChild(UI* _child) { mChildUI.push_back(_child); }


private:
	std::vector<UI*> mChildUI;
	UI*				 mParentUI;
	Texture*		 mTexture;
	bool			 mCamMode;
};

