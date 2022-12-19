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
{

	for (int i = 0; i < (UINT)EQUIP_TYPE::END; ++i)
	{
		ItemUI* itemUI = new ItemUI;
		itemUI->SetParentUI(this);
		mEquipMap.insert(std::make_pair((EQUIP_TYPE)i, itemUI));
		AddChild(itemUI);
	}

	SetType(OBJECT_TYPE::UNIQUE_UI);
	SetUIType(UI_TYPE::INVENTORY);

	mEquipMap[EQUIP_TYPE::WEAPON_LEFT]->SetPos(Vec2(104, 165));
	mEquipMap[EQUIP_TYPE::WEAPON_RIGHT]->SetPos(Vec2(324, 165));

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
		if (nullptr != player)
		{
			if (nullptr != player->GetEquipItem(EQUIP_TYPE::WEAPON_LEFT))
			{
				mEquipMap[EQUIP_TYPE::WEAPON_LEFT]->SetItem(player->GetEquipItem(EQUIP_TYPE::WEAPON_LEFT));
			}

			if (nullptr != player->GetEquipItem(EQUIP_TYPE::WEAPON_RIGHT))
			{
				mEquipMap[EQUIP_TYPE::WEAPON_RIGHT]->SetItem(player->GetEquipItem(EQUIP_TYPE::WEAPON_RIGHT));
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



void InventoryUI::ChangeSlot()
{
	mSlot = (INVENTORY_SLOT)(((int)mSlot + 1) % 2);
}
