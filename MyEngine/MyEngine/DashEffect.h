#pragma once
#include "Effect.h"
#define AFTER_IMAGE_TOTAL 4


class DashEffect :
    public Effect
{
public:
    DashEffect();
    ~DashEffect();

public:
    virtual void Update() override;
    virtual void Render() override;

public:
    void Reset();

private:
    BLENDFUNCTION   mBlendFunc;
    float           mCurDuration;
    float           mDuration;

    Vec2            mStayPos[AFTER_IMAGE_TOTAL];
    float           mCurStayTime;
    float           mStayTime;

    int             mImgCount;
    int             mCurImg;
};

