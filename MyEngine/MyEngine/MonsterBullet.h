#pragma once
#include "Bullet.h"
class Sound;
class MonsterBullet :
    public Bullet
{
public:
    MonsterBullet();
    virtual ~MonsterBullet();

public:
    virtual void Initialize();
    virtual void Update();
    virtual void Render();

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);

public:
    inline void SetBulletWayType(BULLET_WAY_TYPE _type) { mType = _type; }
    inline BULLET_WAY_TYPE GetBulletWayType() const { return mType; }

    inline void SetStandardBullet(MonsterBullet* _bullet) { mStandard = _bullet; }
    inline MonsterBullet* GetStandardBullet() const { return mStandard; }

    inline void  SetAngle(float _angle) { mAngle = _angle; }
    inline float GetAngle() const { return mAngle; }

    inline void SetRadius(float _radius) { mRadius = _radius; }
    inline float GetRadius() const { return mRadius; }

    inline Vec2 GetDir() const { return mDir; }
    inline void SetDir(Vec2 _dir) { mDir = _dir; }

    inline void AddChildBullet(MonsterBullet* _child) { mChildBullets.push_back(_child); }
    inline void ClearChildBullet() { mChildBullets.clear(); }
    bool AllDeadChildBullet();
    inline size_t GetChildSize() const { return mChildBullets.size(); }
    void ChildColliderOn();
    void SetAllDeadAnimChildBullet();
    
    inline void SetHitSound(Sound* _sound) { mSound = _sound; };
    inline Sound* GetHitSound() const { return mSound; };

private:
    Sound* mSound;
    MonsterBullet* mStandard;
    BULLET_WAY_TYPE mType;

    float mAngle;
    float mRadius;
    Vec2 mDir;

    std::vector<MonsterBullet*> mChildBullets;
};

