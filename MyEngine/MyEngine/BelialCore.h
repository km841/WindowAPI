#pragma once
#include "MonsterEffect.h"
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
    virtual void OnCollision(Collider* _other) {}
    virtual void OnCollisionEnter(Collider* _other) {}
    virtual void OnCollisionExit(Collider* _other) {}
};

