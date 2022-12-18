#pragma once
#include "Scene.h"

class TownScene :
    public Scene
{
public:
	TownScene();
	virtual ~TownScene();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	virtual void Enter();
	virtual void Exit();
	virtual void SetCollisionFlag();

private:


};

