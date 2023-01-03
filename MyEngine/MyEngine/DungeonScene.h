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

	inline Stage* GetCurStage() const { return mCurStage; }
	inline Stage* GetStage(STAGE_TYPE _type) { return mStages[(UINT)_type]; }

	void ChangeStage(STAGE_TYPE _type);

protected:
	Stage* mStages[(UINT)STAGE_TYPE::END];
	Stage* mCurStage;

	

	bool mClear;
};

