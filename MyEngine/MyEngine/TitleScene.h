#pragma once
#include "Scene.h"
class Texture;
class TitleScene
	: public Scene
{
public:
	TitleScene();
	virtual ~TitleScene();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	virtual void Enter();
	virtual void Exit();

private:

};

