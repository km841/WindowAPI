#include "pch.h"
#include "ItemInfoHUD.h"
#include "FontMgr.h"
#include "ResourceMgr.h"
#include "Texture.h"

ItemInfoHUD::ItemInfoHUD()
{
	mBaseTex = ResourceMgr::GetInstance().CreateTexture(L"ItemInfoHUDTex", Vec2(300, 300));
	mInfoBase = ResourceMgr::GetInstance().Load<Texture>(L"InfoBase", L"Texture\\InfoBase.bmp");

	mBlendFunc = {};
	mBlendFunc.BlendFlags = 0;
	mBlendFunc.AlphaFormat = 0;
	mBlendFunc.BlendOp = AC_SRC_OVER;
	mBlendFunc.SourceConstantAlpha = 160;
}

ItemInfoHUD::~ItemInfoHUD()
{
}

void ItemInfoHUD::Initialize()
{
	HUD::Initialize();
}

void ItemInfoHUD::Update()
{
	if (GetState())
	{
		HUD::Update();
	}
}

void ItemInfoHUD::Render()
{
	if (GetState() && nullptr != mBaseTex)
	{
		HUD::Render();

		Vec2 baseSize = mBaseTex->GetSize();
		Vec2 infoBaseSize = mInfoBase->GetSize();

		Vec2 pos = GetPos();

		AlphaBlend(
			BACK_BUF_DC,
			(int)(pos.x - baseSize.x),
			(int)pos.y,
			(int)baseSize.x,
			(int)baseSize.y,
			mBaseTex->GetDC(),
			0, 0,
			(int)baseSize.x,
			(int)baseSize.y,
			mBlendFunc
		);

		TransparentBlt(
			BACK_BUF_DC,
			(int)(pos.x - baseSize.x + (infoBaseSize.x / 2.f) - 30.f),
			(int)(pos.y + baseSize.y / 2.f - (infoBaseSize.y)),
			(int)infoBaseSize.x,
			(int)infoBaseSize.y,
			mInfoBase->GetDC(),
			0, 0,
			(int)infoBaseSize.x,
			(int)infoBaseSize.y,
			RGB(255, 0, 255)
		);
		
		if (nullptr != mSetupItemTex)
		{
			Vec2 itemTexSize = mSetupItemTex->GetSize();
			TransparentBlt(
				BACK_BUF_DC,
				(int)(pos.x - baseSize.x + (infoBaseSize.x / 2.f) - 7.f),
				(int)(pos.y + baseSize.y / 2.f - infoBaseSize.y / 2.f - (itemTexSize.y / 2.f)),
				(int)itemTexSize.x,
				(int)itemTexSize.y,
				mSetupItemTex->GetDC(),
				0, 0,
				(int)itemTexSize.x,
				(int)itemTexSize.y,
				RGB(255, 0, 255)
			);
		}

		if (nullptr != mItemNameTex)
		{
			Vec2 itemNameTexSize = mItemNameTex->GetSize();
			TransparentBlt(
				BACK_BUF_DC,
				(int)(pos.x - baseSize.x / 2.f - itemNameTexSize.x / 2.f),
				(int)(pos.y - itemNameTexSize.y / 2.f + 20.f),
				(int)itemNameTexSize.x,
				(int)itemNameTexSize.y,
				mItemNameTex->GetDC(),
				0, 0,
				itemNameTexSize.x,
				itemNameTexSize.y,
				RGB(255, 0, 255)
			);
		}

		if (nullptr != mItemCommentTex)
		{
			Vec2 itemCommentTexOrgSize = mItemCommentTex->GetSize();
			Vec2 itemCommentTexSize = (itemCommentTexOrgSize / 5.f) * 4.f;
			TransparentBlt(
				BACK_BUF_DC,
				(int)(pos.x - baseSize.x / 2.f - itemCommentTexSize.x / 2.f),
				(int)(pos.y - itemCommentTexSize.y / 2.f + 250.f),
				(int)itemCommentTexSize.x,
				(int)itemCommentTexSize.y,
				mItemCommentTex->GetDC(),
				0, 0,
				mItemCommentTex->GetWidth(),
				mItemCommentTex->GetHeight(),
				RGB(255, 0, 255)
			);
		}

		SetState(false);
	}
}

void ItemInfoHUD::SetupItemInfo(Texture* _itemTex, const std::wstring& _itemName, const std::wstring& _itemComment, RARITY _rarity)
{
	mSetupItemTex = _itemTex;
	mItemNameTex = FontMgr::GetInstance().GetTextTexture(_itemName, _itemName);
	mItemCommentTex = FontMgr::GetInstance().GetTextTexture(_itemComment, _itemComment);

	if (nullptr != mItemNameTex)
	{
		COLORREF color = RGB(255, 255, 255);
		switch (_rarity)
		{
		case RARITY::NORMAL:
			break;
		case RARITY::RARE:
			color = RGB(0, 0, 255);
			break;
		case RARITY::UNIQUE:
			color = RGB(255, 0, 254);
			break;
		}

		for (int y = 0; y < mItemNameTex->GetHeight(); ++y)
		{
			for (int x = 0; x < mItemNameTex->GetWidth(); x++)
			{
				Pixel pixel = GetPixel(mItemNameTex->GetDC(), x, y);
				if (pixel.IsWhite())
				{
					SetPixel(mItemNameTex->GetDC(), x, y, color);
				}
			}
		}
	}

}

void ItemInfoHUD::Destroy()
{
	HUD::Destroy();
}
