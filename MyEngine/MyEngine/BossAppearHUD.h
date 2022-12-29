#pragma once
#include "HUD.h"

class Texture;
class BossAppearHUD :
    public HUD
{
public:
    BossAppearHUD();
    virtual ~BossAppearHUD();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

public:
    BLENDFUNCTION mBlendFunc;
    float mMaxDuration;
    float mCurDuration;

    Texture* mTex;

    float mAlpha;

    bool mBrightened;

    float mStayCurDuration;
    float mStayMaxDuration;

};

