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
#include "FontMgr.h"
#include "Sound.h"

InventoryUI::InventoryUI()
	: UI(false)
	, mNextSlotPos(0.f, 0.f)
	, mMoney(0)
	, mSlot(INVENTORY_SLOT::LEFT_SLOT)
	, mLeftBaseTex(nullptr)
	, mRightBaseTex(nullptr)
	, mNextInvenSlot(INVENTORY_SLOT_TYPE::INVEN_R1_C1)
	, mSound(nullptr)
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

	mEquipMap[EQUIP_TYPE::WEAPON_LEFT]->SetPos(Vec2(109, 172));
	mEquipMap[EQUIP_TYPE::WEAPON_RIGHT]->SetPos(Vec2(339, 172));

	Vec2 invenFirstPos = Vec2(82, 420);
	int rowSize = 3;
	int colSize = 5;
	float invenOffset = 94;

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
	mLeftBaseTex = LOAD_TEXTURE(L"inven_left", L"Texture\\inventory_1_slot.bmp");
	mRightBaseTex = LOAD_TEXTURE(L"inven_right", L"Texture\\inventory_2_slot.bmp");

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
		PlayerMoneyRender();
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

void InventoryUI::PlayerMoneyRender()
{
	Vec2 pos = GetPos();
	Player* player = Player::GetPlayer();
	Vec2 moneyPos = pos + Vec2(440, WINDOW_HEIGHT_SIZE - 46);

	int money = player->GetMoney();
	std::wstring moneyText = std::to_wstring(money);

	Texture* moneyTex = FontMgr::GetInstance().GetTextTexture(moneyText, moneyText);
	Vec2 moneyTexOrgSize = moneyTex->GetSize();
	Vec2 moneyTexSize = (moneyTexOrgSize / 2.f) * 3.f;
	TransparentBlt(
		BACK_BUF_DC,
		(int)(moneyPos.x - moneyTexSize.x),
		(int)(moneyPos.y - moneyTexSize.y / 2.f),
		(int)(moneyTexSize.x),
		(int)(moneyTexSize.y),
		moneyTex->GetDC(),
		0, 0,
		(int)moneyTexOrgSize.x,
		(int)moneyTexOrgSize.y,
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
			if (nullptr != mInventoryMap[mNextInvenSlot]->GetItem())
			{
				mNextInvenSlot = (INVENTORY_SLOT_TYPE)((UINT)mNextInvenSlot + 1);
			}
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

void InventoryUI::AddItem(Item* _item)
{
	mInventoryMap[mNextInvenSlot]->SetItem(_item);
}



inline void InventoryUI::SetEquipMap(EQUIP_TYPE _type, Item* _item)
{
	mEquipMap[_type]->SetItem(_item);
}

void InventoryUI::ChangeSlot()
{
	mSlot = (INVENTORY_SLOT)(((int)mSlot + 1) % 2);
}
