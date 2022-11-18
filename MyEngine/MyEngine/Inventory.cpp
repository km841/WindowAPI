#include "pch.h"
#include "Inventory.h"
#include "Item.h"
#include "KeyMgr.h"
#include "MouseMgr.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "ShortSword.h"
#include "GreatSword.h"

Inventory::Inventory()
	: mRender(false)
	, mNextSlotPos(0.f, 0.f)
	, mMoney(0)
	, mSlot(INVENTORY_SLOT::LEFT_SLOT)
	, mLeftBaseTex(nullptr)
	, mRightBaseTex(nullptr)
{
	for (int y = 0; y < Y_SLOT_MAX; ++y)
	{
		for (int x = 0; x < X_SLOT_MAX; ++x)
		{
			mInventory.insert(std::make_pair(Vec2(y, x), nullptr));
		}
	}

	for (int i = 0; i < (UINT)ITEM_TYPE::END; ++i)
	{
		mEquipItems[i] = nullptr;
	}
}

Inventory::~Inventory()
{
	for (int i = 0; i < (UINT)ITEM_TYPE::END; ++i)
	{
		if (nullptr != mEquipItems[i])
		{
			delete mEquipItems[i];
			mEquipItems[i] = nullptr;
		}
	}

	for (auto& item : mInventory)
	{
		if (nullptr != item.second)
		{
			delete item.second;
			item.second = nullptr;
		}

	}

}

void Inventory::Initialize()
{
	mLeftBaseTex = ResourceMgr::GetInstance().Load<Texture>(L"inven_left", L"Texture\\inventory_1_slot.bmp");
	mRightBaseTex = ResourceMgr::GetInstance().Load<Texture>(L"inven_right", L"Texture\\inventory_2_slot.bmp");

	if (nullptr == mLeftBaseTex || nullptr == mRightBaseTex)
		assert(nullptr);
	
	Vec2 size = mLeftBaseTex->GetSize();

	SetPos(Vec2(WINDOW_WIDTH_SIZE - size.x, 0.f));
	SetSize(size);

	ShortSword* shortSword = new ShortSword;
	shortSword->Initialize();
	SetEquipItem(shortSword);

	//GreatSword* greatSword = new GreatSword;
	//greatSword->Initialize();
	//SetEquipItem(greatSword);


}

void Inventory::Update()
{
}

void Inventory::Render()
{
	if (mRender)
	{
		if (nullptr != mLeftBaseTex && nullptr != mRightBaseTex)
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
	}
}

void Inventory::EquipItemUpdate()
{
	for (int i = 0; i < (UINT)ITEM_TYPE::END; ++i)
	{
		if (nullptr != mEquipItems[i])
			mEquipItems[i]->Update();
	}
}

void Inventory::EquipItemRender()
{
	for (int i = 0; i < (UINT)ITEM_TYPE::END; ++i)
	{
		if (nullptr != mEquipItems[i])
			mEquipItems[i]->Render();
	}
}

void Inventory::SetEquipItem(Item* _item)
{
	ITEM_TYPE itemType = _item->GetItemType();
	mEquipItems[(UINT)itemType] = _item;
}

void Inventory::ChangeSlot()
{
	mSlot = (INVENTORY_SLOT)(((int)mSlot + 1) % 2);
}
