#pragma once
#include "MonsterState.h"
class MonsterAttState :
    public MonsterState
{
public:
    MonsterAttState();
    virtual ~MonsterAttState();

public:
    virtual void Update();

public:
    virtual void Enter();
    virtual void Exit();

private:
    float mStayDuration;
    float mMaxStayDuration;

    bool mAttFinFlag;
};

