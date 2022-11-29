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
    virtual void Render();

public:
    virtual void Enter();
    virtual void Exit();

public:
    

private:


};

