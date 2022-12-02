#pragma once
#include "Effect.h"
class MonsterEffect :
    public Effect
{
public:
    MonsterEffect();
    virtual ~MonsterEffect();

public:
    virtual void Update() = 0;
    virtual void Render() {}

public:
    virtual void OnCollision(Collider* _other) {}
    virtual void OnCollisionEnter(Collider* _other) {}
    virtual void OnCollisionExit(Collider* _other) {}
};

