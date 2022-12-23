#pragma once
#include "MonsterMissileEffect.h"
class IceCubesMissileEffect :
    public MonsterMissileEffect
{
public:
    IceCubesMissileEffect();
    virtual ~IceCubesMissileEffect();

public:
    virtual void Initialize();
    virtual void Update();
    virtual void Render();
    virtual void Destroy();

public:
    bool Skill();

private:
    float mMaxDuration;
    float mCurDuration;
    float mMaxBulletCount;
    float mCurBulletCount;

    Vec2 mPlayerDir;


};

