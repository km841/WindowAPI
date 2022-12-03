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
    inline void SetBulletState(bool _flag) { mState = _flag; }
    inline bool GetBulletState() const { return mState; }

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);

private:
    bool mState;

};

