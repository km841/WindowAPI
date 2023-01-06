#pragma once
#include "Scene.h"

class Texture;
class EndingScene :
    public Scene
{
public:
	EndingScene();
	virtual ~EndingScene();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	virtual void Enter();
	virtual void Exit();

private:
	BLENDFUNCTION mBlendFunc;
	Texture* mBackground;

	bool mCameraBegin;

	float mReadyMaxTime;
	float mReadyCurTime;
};

