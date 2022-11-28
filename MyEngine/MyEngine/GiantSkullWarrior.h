#pragma once
#include "Monster.h"
class GiantSkullWarrior :
    public Monster
{
public:
    GiantSkullWarrior();
    virtual ~GiantSkullWarrior();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;

private:



};

