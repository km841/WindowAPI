#pragma once
#include "GameObject.h"
class Bullet :
    public GameObject
{
public:
    Bullet();
    virtual ~Bullet();

public:
    virtual void Initialize();
    virtual void Update();
    virtual void Render();

public:
    inline void       SetBulletInfo(BulletInfo _info) { mInfo = _info; }
    inline BulletInfo GetBulletInfo() const { return mInfo; }

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);


protected:
    BulletInfo mInfo;

};

