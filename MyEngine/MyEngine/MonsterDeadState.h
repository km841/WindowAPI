#pragma once
#include "MonsterState.h"
class MonsterDeadState :
    public MonsterState
{
public:
    MonsterDeadState();
    virtual ~MonsterDeadState();

public:
    virtual void Update();
    virtual void Render();

public:
    virtual void Enter();
    virtual void Exit();
};

