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

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);

public:
    inline void  SetAngle(float _angle) { mAngle = _angle; }
    inline float GetAngle() const { return mAngle; }

    inline Vec2 GetDir() const { return mDir; }
    inline void SetDir(Vec2 _dir) { mDir = _dir; }

private:
    float mAngle;
    Vec2 mDir;
};

