#include "pch.h"
#include "ItemUI.h"
#include "Texture.h"
#include "MouseMgr.h"
#include "InventoryUI.h"
#include "EventRegisteror.h"
#include "UIMgr.h"
#include "ItemInfoHUD.h"
#include "Item.h"
#include "FontMgr.h"

ItemUI::ItemUI()
	:UI(false)
{
	
}

ItemUI::~ItemUI()
{
}

void ItemUI::Initialize()
{
}

void ItemUI::Update()
{
	if (GET_INVENTORY_UI->GetState())
	{
		if (OnMouse())
		{
			if (nullptr != mItem)
			{
				GET_ITEMINFO_HUD->SetPos(MOUSE_POS);
				GET_ITEMINFO_HUD->SetupItemInfo(mItem->GetEquipedTexture(), mItem->GetItemName(), mItem->GetItemComment(), mItem->GetRarity());
				EventRegisteror::GetInstance().EnableHUD(HUD_TYPE::ITEM_INFO);

				if (OnClicked())
				{
					int a = 0;
				}
			}

		}
	}
}

void ItemUI::Render()
{
	Vec2 parentPos = GetParentUI()->GetPos();
	Vec2 pos = GetPos();
	Vec2 uiPos = parentPos + pos;
	
	if (nullptr != mItem)
	{
		Texture* tex = mItem->GetEquipedTexture();
		if (nullptr != tex)
		{
			Vec2 size = tex->GetSize();

			TransparentBlt(BACK_BUF_DC,
				(int)(uiPos.x - size.x / 2.f),
				(int)(uiPos.y - size.y / 2.f),
				(int)size.x,
				(int)size.y,
				tex->GetDC(),
				0, 0,
				(int)size.x,
				(int)size.y,
				RGB(255, 0, 255)
			);

			const std::wstring& itemName = mItem->GetItemName();
			


		}

	}

}

void ItemUI::Destroy()
{
}

bool ItemUI::OnMouse()
{
	InventoryUI* parentUI = static_cast<InventoryUI*>(GetParentUI());
	Vec2 mousePos = MOUSE_POS;

	Vec2 parentPos = parentUI->GetPos();
	Vec2 pos = parentPos + GetPos();

	return (pos.x - 40.f <= mousePos.x && pos.x + 40.f >= mousePos.x &&
		pos.y - 40.f <= mousePos.y && pos.y + 40.f >= mousePos.y);
}

bool ItemUI::OnClicked()
{
	return OnMouse() && IS_LBUTTON_CLICKED;
}
