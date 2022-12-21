#pragma once
#include "MonsterMissileEffect.h"

class MonsterBullet;
class RotateMissileEffect :
    public MonsterMissileEffect
{
public:
    RotateMissileEffect();
    virtual ~RotateMissileEffect();

public:
    virtual void Initialize();
    virtual void Update();
    virtual void Render();
    virtual void Destroy();

public:
    virtual bool Attack();

private:
    std::vector<MonsterBullet*> mCoreBullets;
    MonsterBullet* mCurCoreBullet;

    float          mRadius;
    float          mOmega;
    float          mAngle;

private:
    Vec2 mPlayerVec;

private:
    float          mBulletInterval;
    float          mCurTime;
    float          mMaxBullet;
    bool           mReady;

};

