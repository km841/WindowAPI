#include "pch.h"
#include "Inventory.h"
#include "Item.h"
#include "KeyMgr.h"
#include "MouseMgr.h"
#include "Texture.h"
#include "ResourceMgr.h"

Inventory::Inventory()
	: mRender(false)
	, mNextSlotPos(0.f, 0.f)
	, mMoney(0)
	, mSlot(0)
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
}

void Inventory::Initialize()
{
	mLeftBaseTex = ResourceMgr::GetInstance().Load<Texture>(L"inven_left", L"Texture\\inventory_1_slot.bmp");
	mRightBaseTex = ResourceMgr::GetInstance().Load<Texture>(L"inven_left", L"Texture\\inventory_2_slot.bmp");

	if (nullptr == mLeftBaseTex || nullptr == mRightBaseTex)
		assert(nullptr);
	
	Vec2 size = mLeftBaseTex->GetSize();

	SetPos(Vec2(WINDOW_WIDTH_SIZE - size.x, 0.f));
	SetSize(size);
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
			switch (mSlot)
			{
			case 0:
			
				TransparentBlt(
					BACK_BUF_DC,
					(int)pos.x,
					(int)pos.y,
					(int)size.x,
					(int)size.y,
					mLeftBaseTex->GetDC(),
					0, 0,
					(int)size.x,
					(int)size.y,
					RGB(255, 0, 255)
				);
				break;


			case 1:
			
				TransparentBlt(
					BACK_BUF_DC,
					(int)pos.x,
					(int)pos.y,
					(int)size.x,
					(int)size.y,
					mRightBaseTex->GetDC(),
					0, 0,
					(int)size.x,
					(int)size.y,
					RGB(255, 0, 255)
				);
				break;


			}
		}
	}
}

void Inventory::SetEquipItem(Item* _item)
{
	ITEM_TYPE itemType = _item->GetItemType();
	mEquipItems[(UINT)itemType] = _item;
}
