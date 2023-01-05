#pragma once
#include "UI.h"

class Sound;
class Texture;
class DungeonClearUI :
    public UI
{
public:
    DungeonClearUI();
    virtual ~DungeonClearUI();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;

public:
    virtual bool OnMouse();
    virtual bool OnClicked();

public:
    void SetupTexture(UINT _time, UINT _killCount, int _money);

private:
    Sound* mSound;

    Texture* mMoneyTex;
    Texture* mKillTex;
    Texture* mTimeTex;
    Texture* mPlaceTex;
    Texture* mBossNameTex;

    Texture* mTex;
    Texture* mBaseTex;
    Texture* mSuccessTex;
    BLENDFUNCTION mBaseBlendFunc;
    BLENDFUNCTION mSuccessUIBlendFunc;
    BLENDFUNCTION mLogUIBlendFunc;

    bool mSuccessUIBegin;
    bool mSuccessUIShowComplete;
    bool mSuccessUIStayComplete;
    bool mSuccessUIMoveComplete;
    bool mClearLogBegin;

    float mSuccessUIShowMaxTime;
    float mSuccessUIShowCurTime;

    float mSuccessUIStayMaxTime;
    float mSuccessUIStayCurTime;

    float mSuccessUIMoveMaxTime;
    float mSuccessUIMoveCurTime;

    float mClearLogShowMaxTime;
    float mClearLogShowCurTime;

    bool mClearUIComplete;

    Vec2 mSuccessUIPos;
    float mDistance;
    float mSpeed;
    
    
};

