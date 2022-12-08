#pragma once
#include "GameObject.h"
class DamageObject :
    public GameObject
{
public:
    DamageObject();
    virtual ~DamageObject();

public:
    virtual void Initialize();
    virtual void Update();
    virtual void Render();

public:
    inline void  SetAngle(float _angle) { mAngle = _angle; }
    inline float GetAngle() const { return mAngle; }

    inline void SetCenter(Vec2 _center) { mCenter = _center; }
    inline Vec2 GetCenter() const { return mCenter; }

    inline void SetRadius(float _radius) { mRadius = _radius; }
    inline float GetRadius() const { return mRadius; }

    inline void     SetTexture(Texture* _tex) { mTex = _tex; }
    inline Texture* GetTexture() const { return mTex; }

private:
    float mAngle;
    float mRadius;
    float mAlpha;
    Vec2  mCenter;
    BLENDFUNCTION mBlendFunc;

    Texture* mTex;

};

