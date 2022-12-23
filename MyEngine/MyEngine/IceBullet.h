#pragma once
#include "MonsterBullet.h"
class IceBullet :
    public MonsterBullet
{
public:
    IceBullet();
    virtual ~IceBullet();

public:
    virtual void Initialize();
    virtual void Update();
    virtual void Render();

    virtual void Dead();

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);

public:
    bool mInitFlag;
    std::wstring mAnimName;

};

