#pragma once
#include "UI.h"
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

private:
    Texture* mTex;
    Texture* mBaseTex;
    Texture* mSuccessTex;
    BLENDFUNCTION mBaseBlendFunc;
    BLENDFUNCTION mSuccessUIBlendFunc;
    BLENDFUNCTION mLogUIBlendFunc;

    bool mSuccessUIBegin;
    bool mSuccessUIShowComplete;
    bool mSuccessUIMoveComplete;
    bool mClearLogBegin;

    float mSuccessUIShowMaxTime;
    float mSuccessUIShowCurTime;

    float mSuccessUIMoveMaxTime;
    float mSuccessUIMoveCurTime;

    float mClearLogShowMaxTime;
    float mClearLogShowCurTime;

    bool mClearUIComplete;

    Vec2 mSuccessUIPos;
    float mDistance;
    float mSpeed;
    
    
};

