#pragma once
#include "MonsterMissileEffect.h"
class IceMageMissileEffect :
    public MonsterMissileEffect
{
public:
    IceMageMissileEffect();
    virtual ~IceMageMissileEffect();

public:
    virtual void Initialize();
    virtual void Update();
    virtual void Render();

public:
    virtual bool Attack();

private:
    bool mAttFlag;
    bool mAttCompleteFlag;

    int  mBulletMaxSize;
    float mInitDegree;
    float mDegreeOffset;
};

