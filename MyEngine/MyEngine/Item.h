#pragma once
#include "GameObject.h"

class Texture;


class Item :
    public GameObject
{
public:
    Item();
    virtual ~Item();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

public:
    inline ITEM_TYPE GetItemType() const { return mItemType; }
    inline void     SetItemType(ITEM_TYPE _itemType) { mItemType = _itemType; }

    inline Texture* GetTexture() const { return mTexture; }
    inline void     SetTexture(Texture* _tex) { mTexture = _tex; }

    inline Texture* GetIconTexture() const { return mTexture; }
    inline void     SetIconTexture(Texture* _tex) { mTexture = _tex; }

    inline ItemInfo GetItemInfo() const { return mItemInfo; }
    inline void     SetItemInfo(ItemInfo _info) { mItemInfo = _info; }

private:
    ITEM_TYPE mItemType;
    ItemInfo  mItemInfo;
    Texture*  mTexture;
    Texture*  mIconTexture;
};

