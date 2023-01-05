#pragma once
#include "MonsterState.h"
class BossIdleState :
    public MonsterState
{
public:
    BossIdleState();
    virtual ~BossIdleState();
 
public:
    virtual void Update();
    virtual void Render();

public:
    virtual void Enter();
    virtual void Exit();

private:
    BOSS_CONTROL_STATE mState;
};

