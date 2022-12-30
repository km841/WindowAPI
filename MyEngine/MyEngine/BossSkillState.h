#pragma once
#include "MonsterState.h"
class BossSkillState :
    public MonsterState
{
public:
    BossSkillState();
    virtual ~BossSkillState();

public:
    virtual void Update();
    virtual void Render();

public:
    virtual void Enter();
    virtual void Exit();


private:
    bool mStartFlag;
};

