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

private:
    float mAngle;
    GameObject* mTarget;
    std::vector<AfterImage*> mAfterImages;
    // �ش� �������� �ִϸ��̼ǰ� ��ġ�� �����صΰ� ������ ������� ������Ʈ

    float mMaxDuration;
    float mCurDuration;
    
};

