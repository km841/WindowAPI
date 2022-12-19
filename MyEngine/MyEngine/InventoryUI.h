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



public:
    inline Player* GetPlayer() { return mPlayer; }
    inline void    SetPlayer(Player* _player) { mPlayer = _player; }

    inline INVENTORY_SLOT GetSlot() const { return mSlot; }

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

};

