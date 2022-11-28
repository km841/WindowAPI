#pragma once
#include "MonsterState.h"
class MonsterTraceState
	: public MonsterState
{
public:
    MonsterTraceState();
    virtual ~MonsterTraceState();

public:
    virtual void Update();

public:
    virtual void Enter();
    virtual void Exit();

private:


};

