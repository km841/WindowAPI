#pragma once
#include "MonsterState.h"
class MonsterIdleState :
    public MonsterState
{
public:
    MonsterIdleState();
    virtual ~MonsterIdleState();

public:
    virtual void Update();
    virtual void Render();

public:
    virtual void Enter();
    virtual void Exit();

private:
    float mStayTime;
    float mMaxStayTime;

};

