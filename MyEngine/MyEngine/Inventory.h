#pragma once
#include "GameObject.h"

#define Y_SLOT_MAX 3
#define X_SLOT_MAX 5

class UI;
class Item;
class Player;
class Texture;

class Inventory :
    public GameObject
{
    using SlotMap = std::map<Vec2, Item*>;

public:
    Inventory();
    virtual ~Inventory();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;

public:
    inline Item* GetEquipItem(ITEM_TYPE _itemType) const { return mEquipItems[(UINT)_itemType]; }
    void         SetEquipItem(Item* _item);

    inline Player* GetPlayer() { return mPlayer; }
    inline void    SetPlayer(Player* _player) { mPlayer = _player; }

    inline void SetRender(bool _flag = true) { mRender = _flag; }
    inline bool GetRender() const { return mRender; }

public:
    void ChangeSlot();

private:
    Player* mPlayer;
    Item*   mEquipItems[(UINT)ITEM_TYPE::END];
    int     mMoney;
    SlotMap mInventory;
    int     mSlot;
    // �� ��ǥ�� �����Ǵ� nullptr�� �ʱ⼼�õ�

    Texture* mLeftBaseTex;
    Texture* mRightBaseTex;
    
    //(0, 0), (0, 1) ������ ǥ�õǰ�, �ڸ��� ��� �� �ڸ��� �ٲ�
    Vec2 mNextSlotPos;
    bool mRender;

};

