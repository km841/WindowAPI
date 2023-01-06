#pragma once
#include "GameObject.h"
class Texture;
class EndingLogo :
    public GameObject
{

public:
	EndingLogo();
	virtual ~EndingLogo();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

private:
	Texture* mTex;
	Texture* mThanksMessage;
};

