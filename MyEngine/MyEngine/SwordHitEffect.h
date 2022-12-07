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
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);

private:
    GameObject* mHitDummy[HIT_MAX];



};

