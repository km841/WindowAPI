#pragma once
#include "MonsterBullet.h"
class Sound;
class BelialCoreBullet :
    public MonsterBullet
{
public:
    BelialCoreBullet();
    virtual ~BelialCoreBullet();

public:
    virtual void Initialize();
    virtual void Update();
    virtual void Render();

    virtual void Dead();

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);

private:
    
};

