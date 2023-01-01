#pragma once
#include "MonsterEffect.h"

#define NUM_SHOTS 4

class BelialCoreParticle;
class BelialCore :
    public MonsterEffect
{
public:
    BelialCore();
    virtual ~BelialCore();

public:
    virtual void Update();
    virtual void Render();

public:
    virtual bool Attack();
    virtual void Dead();
public:
    virtual void OnCollision(Collider* _other) {}
    virtual void OnCollisionEnter(Collider* _other) {}
    virtual void OnCollisionExit(Collider* _other) {}

private:
    float mMaxDuration;
    float mCurDuration;

    float mMaxFired;
    float mCurFired;

    float mShotMaxDuration;
    float mShotCurDuration;

    float mInitAngle;
};

