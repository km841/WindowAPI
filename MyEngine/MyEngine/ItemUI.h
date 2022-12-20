#pragma once
#include "UI.h"

class Item;
class ItemUI :
    public UI
{
public:
	ItemUI();
	virtual ~ItemUI();

	friend class InventoryUI;

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();


public:
	virtual bool OnMouse();
	virtual bool OnClicked();
	bool OnRightClicked();

public:
	inline void SetItem(Item* _item) { mItem = _item; }
	inline Item* GetItem() const { return mItem; }
	void DeliverItem(ItemUI* _itemUI);

	inline void SetEquipType(EQUIP_TYPE _equipType) { mEquipType = _equipType; }
	inline EQUIP_TYPE GetEquipType() const { return mEquipType; }

public:
	EQUIP_TYPE mEquipType;
	Item* mItem;
};

