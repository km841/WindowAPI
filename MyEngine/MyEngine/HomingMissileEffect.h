#pragma once
#include "PlayerEffect.h"

class MagicWandBullet;
class HomingMissileEffect :
    public PlayerEffect
{
public:
    HomingMissileEffect();
    virtual ~HomingMissileEffect();

public:
    virtual void Update();
    virtual void Render();
    virtual void Destroy();

public:
    virtual void Change();

public:
    virtual void OnCollision(Collider* _other) {};
    virtual void OnCollisionEnter(Collider* _other) {};
    virtual void OnCollisionExit(Collider* _other) {};


private:
    std::vector<MagicWandBullet*> mBullets;
    float mTurnDelay;
    float mAngleLimit;

    bool mReload;
    bool mAnimStart;

    float mReloadMaxDelay;
    float mReloadDelay;

    float mVelocity;

    Texture* mReloadTex;
    Texture* mReloadBaseTex;

    Vec2 mOffset;
    float mAcc;


};

