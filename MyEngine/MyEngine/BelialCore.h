#pragma once
#include "MonsterEffect.h"

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

public:
    virtual void OnCollision(Collider* _other) {}
    virtual void OnCollisionEnter(Collider* _other) {}
    virtual void OnCollisionExit(Collider* _other) {}

private:
    float mMaxDuration;
    float mCurDuration;

};

