#pragma once
#include "Stage.h"

class Texture;
class Map;
class Prison
	: public Stage
{
public:
	Prison();
	virtual ~Prison();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	virtual void Enter();
	virtual void Exit();

private:
	Texture* mSubBGTex;
	
};

