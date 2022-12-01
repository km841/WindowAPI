#pragma once
#include "PlayerEffect.h"

class GameObject;

class SwordHitEffect :
    public PlayerEffect
{
public:
    SwordHitEffect();
    virtual ~SwordHitEffect();

public:
    virtual void Update();
    virtual void Render();

public:
    inline void  SetAngle(float _angle) { mAngle = _angle; }
    inline float GetAngle() const { return mAngle; }

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);

private:
    GameObject* mHitDummy[HIT_MAX];
    float     mAngle;


};

