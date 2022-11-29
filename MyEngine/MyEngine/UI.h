#pragma once
#include "GameObject.h"

class Texture;
class UIMgr;
class UI
	: public GameObject
{
public:
	UI(bool _camMode);
	virtual ~UI();

	UI(const UI& _other);

	friend class UIMgr;

public:
	virtual void	Initialize();
	virtual void	Update();
	virtual void	Render();
	virtual void	Destroy();

public:
	virtual bool OnMouse() { return false; }
	virtual bool OnClicked() { return false; }

public:
	inline void		SetTexture(Texture* _tex) { mTexture = _tex; }
	inline Texture* GetTexture() const { return mTexture; }

	inline void		SetParentUI(UI* _parent) { mParentUI = _parent;}
	inline UI*		GetParentUI() { return mParentUI; }

	inline void		AddChild(UI* _child) { mChildUI.push_back(_child); }
	inline const std::vector<UI*>& GetChildUI() const { return mChildUI; }

	inline void SetState(bool _flag = true) { mState = _flag; }
	inline bool GetState() const { return mState; }

	inline void    SetUIType(UI_TYPE _type) { mType = _type; }
	inline UI_TYPE GetUIType() const { return mType; }

	inline void SetOnMouseState(bool _flag) { mOnMouse = _flag; }
	inline void SetOnClickedState(bool _flag) { mOnClicked = _flag; }


private:
	std::vector<UI*> mChildUI;
	UI*				 mParentUI;
	Texture*		 mTexture;
	bool			 mCamMode;
	bool			 mState;
	UI_TYPE			 mType;

protected:
	bool			 mOnMouse;
	bool			 mOnClicked;
};

