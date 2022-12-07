#pragma once
#include "Bullet.h"
class PlayerBullet :
    public Bullet
{
public:
    PlayerBullet();
    virtual ~PlayerBullet();

public:
    virtual void Initialize();
    virtual void Update();
    virtual void Render();

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);
};

