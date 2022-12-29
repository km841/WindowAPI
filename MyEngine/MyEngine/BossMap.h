#pragma once
#include "Map.h"

class BossMonster;
class BossMap :
    public Map
{
public:
	BossMap(const std::wstring& _path);
	virtual ~BossMap();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	virtual void Enter();
	virtual void Exit();

protected:
	BossMonster* mBossMonster;

	float mMaxDuration;
	float mCurDuration;
	

};

