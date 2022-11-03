#pragma once
#include "GameObject.h"
class UI
	: public GameObject
{
public:
	UI(bool _camMode);
	~UI();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();


private:
	std::vector<UI*> mChildUI;
	bool mCamMode;
	bool mOnMouse;
	bool mClicked;
	

};

