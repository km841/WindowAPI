#pragma once
#include "UI.h"

#define Y_SLOT_MAX 3
#define X_SLOT_MAX 5

class UI;
class Item;
class Player;
class Texture;

class InventoryUI :
    public UI
{
    using SlotMap = std::map<Vec2, Item*>;

public:
    InventoryUI();
    virtual ~InventoryUI();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;



public:


    inline Player* GetPlayer() { return mPlayer; }
    inline void    SetPlayer(Player* _player) { mPlayer = _player; }


public:
    void ChangeSlot();

private:

    Player* mPlayer;
    int     mMoney;
    SlotMap mInventory;
    INVENTORY_SLOT mSlot;
    // �� ��ǥ�� �����Ǵ� nullptr�� �ʱ⼼�õ�

    Texture* mLeftBaseTex;
    Texture* mRightBaseTex;
    
    //(0, 0), (0, 1) ������ ǥ�õǰ�, �ڸ��� ��� �� �ڸ��� �ٲ�
    Vec2 mNextSlotPos;

};

