#pragma once
#include "MonsterBullet.h"
class BatBullet :
    public MonsterBullet
{
public:
    BatBullet();
    virtual ~BatBullet();

public:
    virtual void Initialize();
    virtual void Update();
    virtual void Render();

    virtual void Dead();

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);
    
};

