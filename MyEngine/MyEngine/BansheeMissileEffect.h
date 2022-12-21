#pragma once
#include "MonsterMissileEffect.h"
class BansheeMissileEffect :
    public MonsterMissileEffect
{
public:
    BansheeMissileEffect();
    virtual ~BansheeMissileEffect();

public:
    virtual void Initialize();
    virtual void Update();
    virtual void Render();

public:
    virtual bool Attack();

protected:
};

