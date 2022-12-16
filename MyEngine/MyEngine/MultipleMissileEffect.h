#pragma once
#include "MonsterMissileEffect.h"

#define MULTIPLE_BULLET_1TIMES 3

class MultipleMissileEffect :
    public MonsterMissileEffect
{
public:
    MultipleMissileEffect();
    virtual ~MultipleMissileEffect();

public:
    virtual void Initialize();
    virtual void Update();
    virtual void Render();
    virtual void Destroy();

public:
    virtual bool Attack();

private:
    float mMaxDuration;
    float mCurDuration;
    float mAttCount;

    float mStayDuration;
    float mMaxStayDuration;

    Vec2  mDirs[MULTIPLE_BULLET_1TIMES];
};

