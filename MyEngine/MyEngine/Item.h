#pragma once
#include "GameObject.h"

class Texture;
struct ItemInfo
{
    //Stat
};

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

public:
    inline ITEM_TYPE GetItemType() const { return mItemType; }
    inline void SetItemType(ITEM_TYPE _itemType) { mItemType = _itemType; }

    inline Texture* GetTexture() const { return mTexture; }
    inline void SetTexture(Texture* _tex) { mTexture = _tex; }

    inline Texture* GetIconTexture() const { return mTexture; }
    inline void SetIconTexture(Texture* _tex) { mTexture = _tex; }

private:
    ITEM_TYPE mItemType;
    ItemInfo  mItemInfo;
    Texture*  mTexture;
    Texture*  mIconTexture;
};
