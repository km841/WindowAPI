#pragma once
#include "MonsterState.h"
class MonsterPatrolState :
    public MonsterState
{
public:
    MonsterPatrolState();
    virtual ~MonsterPatrolState();

public:
    virtual void Update();
    virtual void Render();

public:
    virtual void Enter();
    virtual void Exit();

public:
    bool PlayerCheck();

private:
    float mDelayMaxTime;
    float mDelayTime;

};
