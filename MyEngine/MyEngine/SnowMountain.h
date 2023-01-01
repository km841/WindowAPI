#pragma once
#include "Stage.h"
class SnowMountain :
    public Stage
{
public:
	SnowMountain();
	virtual ~SnowMountain();

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

