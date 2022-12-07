#pragma once
#include "GameObject.h"

class Texture;
class Bullet;
class AfterImage :
    public GameObject
{
public:
    AfterImage();
    virtual ~AfterImage();

public:
    virtual void Initialize();
    virtual void Update();
    virtual void Render();

public:
    inline void SetLTPos(Vec2 _pos) { mLTPos = _pos; }
    inline Vec2 GetLTPos() const { return mLTPos; }

    inline void SetSliceSize(Vec2 _size) { mSliceSize = _size; }
    inline Vec2 GetSliceSize() const { return mSliceSize; }

    inline void SetAnimation(Animation* _anim) { mAnim = _anim; }
    inline void SetAnimFrame(int _frm) { mFrm = _frm; }

    inline bool IsDead() const { return mDead; }

    inline void    SetOwner(Bullet* _owner) { mOwner = _owner; }
    inline Bullet* GetOwner() const { return mOwner; }

private:
    Texture*      mTex;
    Vec2          mLTPos;
    Vec2          mSliceSize;
    Animation*    mAnim;
    BLENDFUNCTION mBlendFunc;
    Bullet*       mOwner;

    int           mFrm;
    float         mAlpha;
    float         mMaxDuration;
    float         mCurDuration;
    
    bool          mDead;
};

