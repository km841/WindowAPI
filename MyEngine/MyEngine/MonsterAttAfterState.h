#pragma once
#include "MonsterState.h"
class MonsterAttAfterState :
    public MonsterState
{
public:
    MonsterAttAfterState();
    virtual ~MonsterAttAfterState();

public:
    virtual void Update();

public:
    virtual void Enter();
    virtual void Exit();

private:

};

