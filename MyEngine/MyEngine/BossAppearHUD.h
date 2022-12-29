#pragma once
#include "HUD.h"

class Texture;
class BossMonster;
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
    void SetBossMonster(BossMonster* _boss);

public:
    BossMonster* mBoss;
    BLENDFUNCTION mBlendFunc;

    float mMaxDuration;
    float mCurDuration;

    Texture* mTex;

    float mAlpha;

    bool mBrightened;

    float mStayCurDuration;
    float mStayMaxDuration;

    Texture* mBossNameTex;
    Texture* mBossCommentTex;

    Vec2 mBossNamePos;
    Vec2 mBossCommentPos;

};

