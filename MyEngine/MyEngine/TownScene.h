#pragma once
#include "Scene.h"

class TownScene :
    public Scene
{
public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();

public:
	virtual void Enter();
	virtual void Exit();

private:


};

