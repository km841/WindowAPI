#pragma once
#include "PlayerBullet.h"

class AfterImage;
class MagicWandBullet :
    public PlayerBullet
{
public:
    MagicWandBullet();
    virtual ~MagicWandBullet();

public:
    virtual void Initialize();
    virtual void Update();
    virtual void Render();
    virtual void Destroy();

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);

public:
    inline void  SetAngle(float _angle) { mAngle = _angle; }
    inline float GetAngle() const { return mAngle; }

    inline void        SetTarget(GameObject* _target) { mTarget = _target; }
    inline GameObject* GetTarget() const { return mTarget; }

    inline void SetInitDirVector(Vec2 _initDir) { mInitDir = _initDir; }
    inline Vec2 GetInitDirVector() const { return mInitDir; }

    inline void  SetInitCurDuration(float _duration) { mInitCurDuration = _duration; }
    inline float GetInitCurDuration() const { return mInitCurDuration; }

    inline float GetInitMaxDuration() const { return mInitMaxDuration; }

    inline void SetSpeedVector(Vec2 _v) { mSpeedVector = _v; }
    inline Vec2 GetSpeedVector() const { return mSpeedVector; }

private:
    float mAngle;
    GameObject* mTarget;
    std::vector<AfterImage*> mAfterImages;
    // 해당 프레임의 애니메이션과 위치를 저장해두고 서서히 사라지는 오브젝트

    Vec2 mInitDir;
    float mInitMaxDuration;
    float mInitCurDuration;

    float mMaxDuration;
    float mCurDuration;

    Vec2 mSpeedVector;
    
};

