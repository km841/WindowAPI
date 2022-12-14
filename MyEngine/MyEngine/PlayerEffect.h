#pragma once
#include "Effect.h"
class PlayerEffect :
    public Effect
{
public:
    PlayerEffect();
    virtual ~PlayerEffect();

public:
    virtual void Update() = 0;
    virtual void Render() {};

public:
    virtual void Change() {}

public:
    inline void  SetAngle(float _angle) { mAngle = _angle; }
    inline float GetAngle() const { return mAngle; }

public:
    virtual void OnCollision(Collider* _other) = 0;
    virtual void OnCollisionEnter(Collider* _other) = 0;
    virtual void OnCollisionExit(Collider* _other) = 0;

protected:
    float     mAngle;
};

