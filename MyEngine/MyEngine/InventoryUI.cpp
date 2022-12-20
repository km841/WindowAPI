#include "pch.h"
#include "InventoryUI.h"
#include "Item.h"
#include "KeyMgr.h"
#include "MouseMgr.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "ShortSword.h"
#include "GreatSword.h"
#include "Player.h"
#include "ItemUI.h"

InventoryUI::InventoryUI()
	: UI(false)
	, mNextSlotPos(0.f, 0.f)
	, mMoney(0)
	, mSlot(INVENTORY_SLOT::LEFT_SLOT)
	, mLeftBaseTex(nullptr)
	, mRightBaseTex(nullptr)
	, mNextInvenSlot(INVENTORY_SLOT_TYPE::INVEN_R1_C1)
{

	for (int i = 0; i < (UINT)EQUIP_TYPE::END; ++i)
	{
		ItemUI* itemUI = new ItemUI;
		itemUI->SetParentUI(this);
		itemUI->SetEquipType((EQUIP_TYPE)i);
		mEquipMap.insert(std::make_pair((EQUIP_TYPE)i, itemUI));
		AddChild(itemUI);
	}

	SetType(OBJECT_TYPE::UNIQUE_UI);
	SetUIType(UI_TYPE::INVENTORY);

	mEquipMap[EQUIP_TYPE::WEAPON_LEFT]->SetPos(Vec2(104, 165));
	mEquipMap[EQUIP_TYPE::WEAPON_RIGHT]->SetPos(Vec2(324, 165));

	Vec2 invenFirstPos = Vec2(79, 401);
	int rowSize = 3;
	int colSize = 5;
	float invenOffset = 89.5;

	for (int y = 0; y < rowSize; ++y)
	{
		for (int x = 0; x < colSize; ++x)
		{
			ItemUI* itemUI = new ItemUI;
			itemUI->SetParentUI(this);
			itemUI->SetEquipType(EQUIP_TYPE::END);
			itemUI->SetPos(Vec2(invenFirstPos.x + (x * invenOffset), invenFirstPos.y + (y * invenOffset)));
			mInventoryMap.insert(std::make_pair((INVENTORY_SLOT_TYPE)(y * colSize + x), itemUI));
			AddChild(itemUI);
		}
	}

}

InventoryUI::~InventoryUI()
{
}

void InventoryUI::Initialize()
{
	mLeftBaseTex = ResourceMgr::GetInstance().Load<Texture>(L"inven_left", L"Texture\\inventory_1_slot.bmp");
	mRightBaseTex = ResourceMgr::GetInstance().Load<Texture>(L"inven_right", L"Texture\\inventory_2_slot.bmp");

	if (nullptr == mLeftBaseTex || nullptr == mRightBaseTex)
		assert(nullptr);
	
	Vec2 size = mLeftBaseTex->GetSize();

	SetPos(Vec2(WINDOW_WIDTH_SIZE - size.x, 0.f));
	SetSize(size);
}

void InventoryUI::Update()
{
	UI::Update();
}

void InventoryUI::Render()
{
	if (!GetState())
		return;

	if (nullptr != mLeftBaseTex && nullptr != mRightBaseTex)
	{
		InventoryBaseRender();

		Vec2 pos = GetPos();
		
		Player* player = Player::GetPlayer();
		Item* leftItem = player->GetEquipItem(EQUIP_TYPE::WEAPON_LEFT);
		Item* rightItem = player->GetEquipItem(EQUIP_TYPE::WEAPON_RIGHT);

		if (nullptr != player)
		{
			if (nullptr != leftItem)
			{
				mEquipMap[EQUIP_TYPE::WEAPON_LEFT]->SetItem(leftItem);
			}

			if (nullptr != rightItem)
			{
				mEquipMap[EQUIP_TYPE::WEAPON_RIGHT]->SetItem(rightItem);
			}
		}
	}
	UI::Render();
}

void InventoryUI::InventoryBaseRender()
{
	Vec2 pos = GetPos();
	Vec2 size = mLeftBaseTex->GetSize();

	Texture* curBase = nullptr;
	switch (mSlot)
	{
	case INVENTORY_SLOT::LEFT_SLOT:
		curBase = mLeftBaseTex;
		break;

	case INVENTORY_SLOT::RIGHT_SLOT:
		curBase = mRightBaseTex;
		break;
	}

	TransparentBlt(
		BACK_BUF_DC,
		(int)pos.x,
		(int)pos.y,
		(int)size.x,
		(int)size.y,
		curBase->GetDC(),
		0, 0,
		(int)size.x,
		(int)size.y,
		RGB(255, 0, 255)
	);
}

void InventoryUI::UnMountItem(ItemUI* _itemUI)
{
	Item* item = _itemUI->GetItem();
	if (nullptr != item)
	{
		if (INVENTORY_SLOT_TYPE::END != mNextInvenSlot)
		{
			_itemUI->DeliverItem(mInventoryMap[mNextInvenSlot]);
			Player::GetPlayer()->ClearEquipItem(_itemUI->GetEquipType());

			mNextInvenSlot = (INVENTORY_SLOT_TYPE)((UINT)mNextInvenSlot + 1);
		}

		else
		{
			mInvenFullFlag = true;
		}
	}
}

void InventoryUI::MountItem(ItemUI* _itemUI)
{
	Item* item = _itemUI->GetItem();
	if (nullptr != item)
	{
		switch (mSlot)
		{
		case INVENTORY_SLOT::LEFT_SLOT:
		{
			if (nullptr != mEquipMap[EQUIP_TYPE::WEAPON_LEFT]->GetItem())
			{
				Item* otherItem = mEquipMap[EQUIP_TYPE::WEAPON_LEFT]->GetItem();
				_itemUI->DeliverItem(mEquipMap[EQUIP_TYPE::WEAPON_LEFT]);
				_itemUI->SetItem(otherItem);
				Player::GetPlayer()->SetEquipItem(EQUIP_TYPE::WEAPON_LEFT, mEquipMap[EQUIP_TYPE::WEAPON_LEFT]->GetItem());
			}

			else
			{
				_itemUI->DeliverItem(mEquipMap[EQUIP_TYPE::WEAPON_LEFT]);
				Player::GetPlayer()->SetEquipItem(EQUIP_TYPE::WEAPON_LEFT, mEquipMap[EQUIP_TYPE::WEAPON_LEFT]->GetItem());
				mNextInvenSlot = (INVENTORY_SLOT_TYPE)((UINT)mNextInvenSlot - 1);
			}
		}
			break;
		case INVENTORY_SLOT::RIGHT_SLOT:
		{
			if (nullptr != mEquipMap[EQUIP_TYPE::WEAPON_RIGHT]->GetItem())
			{
				Item* otherItem = mEquipMap[EQUIP_TYPE::WEAPON_RIGHT]->GetItem();
				_itemUI->DeliverItem(mEquipMap[EQUIP_TYPE::WEAPON_RIGHT]);
				_itemUI->SetItem(otherItem);
				Player::GetPlayer()->SetEquipItem(EQUIP_TYPE::WEAPON_RIGHT, mEquipMap[EQUIP_TYPE::WEAPON_RIGHT]->GetItem());
			}

			else
			{
				_itemUI->DeliverItem(mEquipMap[EQUIP_TYPE::WEAPON_RIGHT]);
				Player::GetPlayer()->SetEquipItem(EQUIP_TYPE::WEAPON_RIGHT, mEquipMap[EQUIP_TYPE::WEAPON_RIGHT]->GetItem());
				mNextInvenSlot = (INVENTORY_SLOT_TYPE)((UINT)mNextInvenSlot - 1);
			}
		}
			break;
		}
	}
}



inline void InventoryUI::SetEquipMap(EQUIP_TYPE _type, Item* _item)
{
	mEquipMap[_type]->SetItem(_item);
}

void InventoryUI::ChangeSlot()
{
	mSlot = (INVENTORY_SLOT)(((int)mSlot + 1) % 2);
}
