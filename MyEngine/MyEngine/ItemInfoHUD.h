#pragma once
#include "HUD.h"

class Texture;
class ItemInfoHUD :
    public HUD
{
public:
    ItemInfoHUD();
    virtual ~ItemInfoHUD();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

public:
    void SetupItemInfo(Texture* _itemTex, const ItemInfo& _info);

    void ItemTextureRender();
    void ItemNameRender();
    void ItemCommentRender();
    void ItemAttackValueRender();
    void ItemAttackSpeedRender();
    void ItemWeaponTypeRender();

private:
    Texture* mTex;
    Texture* mInfoBase;
    Texture* mBaseTex;
    BLENDFUNCTION mBlendFunc;

    Texture* mSetupItemTex;
    Texture* mItemNameTex;
    Texture* mItemCommentTex;
    Texture* mItemAttTex;
    Texture* mItemAttSpeedTex;
    Texture* mItemWeaponTypeTex;
};

