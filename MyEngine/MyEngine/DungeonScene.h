#pragma once
#include "Scene.h"
class Stage;
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
	virtual void Enter();
	virtual void Exit();

	virtual void SetCollisionFlag();

protected:
	Stage* mStages[(UINT)STAGE_TYPE::END];
	Stage* mCurStage;

	bool mClear;
};

