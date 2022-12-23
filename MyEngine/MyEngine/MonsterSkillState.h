#pragma once
#include "MonsterState.h"
class MonsterSkillState :
    public MonsterState
{
public:
    MonsterSkillState();
    virtual ~MonsterSkillState();

public:
    virtual void Update();
    virtual void Render();

public:
    virtual void Enter();
    virtual void Exit();
};

