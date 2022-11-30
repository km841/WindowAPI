#pragma once
#include "Item.h"

class SwordHitEffect;
class Effect;
class Sword :
    public Item
{
public:
    Sword();
    virtual ~Sword();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;

public:
    inline void SetTransTexture(Texture* _maskTex) { mTransTexture = _maskTex; }
    inline Texture* GetTransTexture() const { return mTransTexture; }

    inline void SetOffset(Vec2 _offset) { mOffset = _offset; }
    inline Vec2 GetOffset() const { return mOffset; }

    inline void SetLeftDirOffset(float _offset) { mXAxisDirOffset[(UINT)DIR::LEFT] = _offset; }
    inline void SetRightDirOffset(float _offset) { mXAxisDirOffset[(UINT)DIR::RIGHT] = _offset; }
    inline float GetLeftDirOffset() const { return mXAxisDirOffset[(UINT)DIR::LEFT]; }
    inline float GetRightDirOffset() const { return mXAxisDirOffset[(UINT)DIR::RIGHT]; }

    inline float GetYOffset() const { return mYAxisOffset; }
    inline void SetYOffset(float _offset) { mYAxisOffset = _offset; }

    inline void SetEffect(SwordHitEffect* _effect) { mHitEffect = _effect; }
    inline SwordHitEffect* GetEffect() const { return mHitEffect; }

    inline void SetSwordState(SWORD_STATE _state) { mState = _state; }
    inline SWORD_STATE GetSwordState() const { return mState; }

    inline void SetPrevSwordState(SWORD_STATE _state) { mPrevState = _state; }
    inline SWORD_STATE GetPrevSwordState() const { return mPrevState; }

    void ChangeSwordState();

    inline float GetAngle() const { return mAngle; }

    inline void SetDuration(float _duration) { mDuration = _duration; }
    inline float GetDuration() const { return mDuration; }



private:
    Vec2 mVertices[(UINT)VERTICES_POINT::END];
    Vec2 mRotatedVertices[(UINT)VERTICES_POINT::END];
    Vec2 mOffset;
    float mXAxisDirOffset[(UINT)DIR::END];
    float mYAxisOffset;
    float mAngle;
    float mDuration;


    SwordHitEffect* mHitEffect;

    Texture* mTransTexture;
    SWORD_STATE mState;
    SWORD_STATE mPrevState;

};

