#pragma once
#include "HUD.h"

class Texture;
class EquipedHUD :
    public HUD
{
public:
    EquipedHUD();
    virtual ~EquipedHUD();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

public:
    inline void SetChangingState(EQUIPED_CHANGING_STATE _flag) { mChangingState = _flag; }
    inline EQUIPED_CHANGING_STATE GetChangingState() const { return mChangingState; }

    inline void ChangeDirSign() { mDir = -mDir; }

private:
    Texture* mTex;

    Vec2 mBackSlotPos;
    Vec2 mBackSlotCurPos;

    Vec2 mFrontSlotPos;
    Vec2 mFrontSlotCurPos;

    EQUIPED_CHANGING_STATE mChangingState;
    float mMaxDuration;
    float mCurDuration;

    float mDistance;
    Vec2  mDir;

    bool mChanged;

};

