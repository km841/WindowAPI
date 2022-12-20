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
    virtual void Change() {}

public:
    inline ITEM_TYPE GetItemType() const { return mItemType; }
    inline void     SetItemType(ITEM_TYPE _itemType) { mItemType = _itemType; }

    inline Texture* GetTexture() const { return mTexture; }
    inline void     SetTexture(Texture* _tex) { mTexture = _tex; }

    inline Texture* GetIconTexture() const { return mTexture; }
    inline void     SetIconTexture(Texture* _tex) { mTexture = _tex; }

    inline Texture* GetEquipedTexture() const { return mEquipedTex; }
    inline void     SetEquipedTexture(Texture* _tex) { mEquipedTex = _tex; }

    inline ItemInfo& GetItemInfo() { return mItemInfo; }
    inline void      SetItemInfo(ItemInfo _info) { mItemInfo = _info; }

    inline void Reload() { mItemInfo.mAmmo = mItemInfo.mMaxAmmo; }

    inline void SetFallen(bool _flag) { mHasFallen = _flag; }
    inline bool HasFallen() const { return mHasFallen; }

    inline void SetItemName(const std::wstring& _name) { mItemName = _name; }
    inline const std::wstring& GetItemName() const { return mItemName; }

    inline void SetItemComment(const std::wstring& _comment) { mItemComment = _comment; }
    inline const std::wstring& GetItemComment() const { return mItemComment; }
    
    inline void   SetRarity(RARITY _rarity) { mRarity = _rarity; }
    inline RARITY GetRarity() const { return mRarity; }

    void Drop(Vec2 _pos);



private:
    ITEM_TYPE mItemType;
    ItemInfo  mItemInfo;
    Texture*  mTexture;
    Texture*  mIconTexture;
    Texture*  mEquipedTex;

    RARITY    mRarity;

    std::wstring mItemName;
    std::wstring mItemComment;

protected:
    bool      mHasFallen;
};

