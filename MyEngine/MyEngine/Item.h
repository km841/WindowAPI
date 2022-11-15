#pragma once
#include "GameObject.h"

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

private:
    ITEM_TYPE mItemType;
    ItemInfo  mItemInfo;
};

