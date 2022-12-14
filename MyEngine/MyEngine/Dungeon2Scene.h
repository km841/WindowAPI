#pragma once
#include "DungeonScene.h"
class Dungeon2Scene :
    public DungeonScene
{
public:
	Dungeon2Scene();
	virtual ~Dungeon2Scene();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	virtual void Enter();
	virtual void Exit();
};

