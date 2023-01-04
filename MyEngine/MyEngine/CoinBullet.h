#pragma once
#include "PlayerBullet.h"

class Sound;
class CoinBullet :
    public PlayerBullet
{
public:
    CoinBullet();
    virtual ~CoinBullet();

public:
    virtual void Initialize();
    virtual void Update();
    virtual void Render();

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);

public:
    inline void SetDir(Vec2 _dir) { mDir = _dir; }

private:
    Sound* mSound;
    Vec2 mDir;

    bool mInvin;
    float mInvinMaxTime;
    float mInvinCurTime;
};

