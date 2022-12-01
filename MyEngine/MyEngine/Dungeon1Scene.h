#pragma once
#include "Scene.h"
class Dungeon1Scene :
    public Scene
{
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

