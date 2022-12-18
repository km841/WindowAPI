#pragma once
#include "Scene.h"
class DungeonScene :
    public Scene
{
public:
	DungeonScene();
	virtual ~DungeonScene();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	virtual void Enter() = 0;
	virtual void Exit() = 0;
};
