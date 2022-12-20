#pragma once
#include "HUD.h"
class Texture;
class ItemGetHUD :
    public HUD
{
public:
    ItemGetHUD();
    virtual ~ItemGetHUD();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

public:
    void SetupItemInfo(Texture* _itemTex, const ItemInfo& _info);

private:
    Texture* mTex;
    Texture* mTextTex;
    BLENDFUNCTION mBlendFunc;

    Texture* mSetupItemTex;
    Texture* mItemNameTex;

    float mMaxDuration;
    float mCurDuration;
};

