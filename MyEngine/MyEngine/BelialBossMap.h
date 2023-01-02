#pragma once
#include "BossMap.h"

class Sound;
class BoomEffect;
class Belial;
class BelialBossMap :
    public BossMap
{
public:
	BelialBossMap(const std::wstring& _path);
	virtual ~BelialBossMap();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	virtual void Enter();
	virtual void Exit();

private:
	Belial* mBelial;

	Sound* mSound;
	
	std::vector<BoomEffect*> mEffects;
	bool mBossAppearing;
	bool mBossActive;
	float mBossActiveArea;

	float mMaxDuration;
	float mCurDuration;


	float mDeadStayMaxTime;
	float mDeadStayCurTime;

	bool mDeadStayFlag;

	int mBoomMaxCount;
	int mBoomCurCount;

	float mBoomMaxTime;
	float mBoomCurTime;
};

