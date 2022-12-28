#pragma once
#include "BossMap.h"
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
};

