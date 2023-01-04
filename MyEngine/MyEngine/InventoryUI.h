#pragma once
#include "UI.h"

#define Y_SLOT_MAX 3
#define X_SLOT_MAX 5

class UI;
class Item;
class Player;
class Texture;
class ItemUI;
class InventoryUI :
    public UI
{

public:
    InventoryUI();
    virtual ~InventoryUI();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;

public:
    void InventoryBaseRender();
    void PlayerMoneyRender();
    void UnMountItem(ItemUI* _item);
    void MountItem(ItemUI* _item);
    void AddItem(Item* _item);


public:
    inline Player* GetPlayer() { return mPlayer; }
    inline void    SetPlayer(Player* _player) { mPlayer = _player; }

    inline INVENTORY_SLOT GetSlot() const { return mSlot; }
    inline void SetEquipMap(EQUIP_TYPE _type, Item* _item);

public:
    void ChangeSlot();
private:

    Player* mPlayer;
    int     mMoney;
    INVENTORY_SLOT mSlot;
    // �� ��ǥ�� �����Ǵ� nullptr�� �ʱ⼼�õ�

    Texture* mLeftBaseTex;
    Texture* mRightBaseTex;
    
    //(0, 0), (0, 1) ������ ǥ�õǰ�, �ڸ��� ��� �� �ڸ��� �ٲ�
    Vec2 mNextSlotPos;

    std::map<EQUIP_TYPE, ItemUI*> mEquipMap;
    std::map<INVENTORY_SLOT_TYPE, ItemUI*> mInventoryMap;
    INVENTORY_SLOT_TYPE mNextInvenSlot;

    bool mInvenFullFlag;

    Sound* mSound;
};

