#pragma once
#include "DungeonScene.h"
class Dungeon1Scene :
    public DungeonScene
{
public:
	Dungeon1Scene();
	virtual ~Dungeon1Scene();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	virtual void Enter();
	virtual void Exit();
};

