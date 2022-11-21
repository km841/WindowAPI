#pragma once
#include "Effect.h"



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

    float           mAlpha;

    float           mCurStayTime;
    float           mStayTime;

};

