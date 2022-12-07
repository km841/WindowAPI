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
    inline void         SetBulletState(BULLET_STATE _flag) { mState = _flag; }
    inline BULLET_STATE GetBulletState() const { return mState; }

    inline void       SetBulletInfo(BulletInfo _info) { mInfo = _info; }
    inline BulletInfo GetBulletInfo() const { return mInfo; }

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);

private:
    BULLET_STATE mState;

protected:
    BulletInfo mInfo;

};

