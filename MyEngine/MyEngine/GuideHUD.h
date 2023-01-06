#pragma once
#include "HUD.h"
class Texture;
class GuideHUD :
    public HUD
{
public:
    GuideHUD();
    virtual ~GuideHUD();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

public:
    void SetupType(SCENE_TYPE _type);

private:
    Texture* mTex;

    bool mComeBegin;
    float mComeMaxTime;
    float mComeCurTime;

    bool mComeComplete;
    float mBackMaxTime;
    float mBackCurTime;

    bool mBackComplete;
    float mStayMaxTime;
    float mStayCurTime;

    bool mStayComplete;
    float mLeaveMaxTime;
    float mLeaveCurTime;

    Vec2 mCurPos;

};

