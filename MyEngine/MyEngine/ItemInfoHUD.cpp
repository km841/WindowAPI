#include "pch.h"
#include "ItemInfoHUD.h"
#include "FontMgr.h"
#include "ResourceMgr.h"
#include "Texture.h"

ItemInfoHUD::ItemInfoHUD()
{
	mBaseTex = ResourceMgr::GetInstance().CreateTexture(L"ItemInfoHUDTex", Vec2(300, 300));
	mInfoBase = LOAD_TEXTURE(L"InfoBase", L"Texture\\InfoBase.bmp");

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
			ItemTextureRender();
		}

		if (nullptr != mItemNameTex)
		{
			ItemNameRender();
		}

		if (nullptr != mItemCommentTex)
		{
			ItemCommentRender();
		}

		if (nullptr != mItemAttTex)
		{
			ItemAttackValueRender();
		}

		if (nullptr != mItemAttSpeedTex)
		{
			ItemAttackSpeedRender();
		}

		if (nullptr != mItemWeaponTypeTex)
		{
			ItemWeaponTypeRender();
		}

		SetState(false);
	}
}

void ItemInfoHUD::SetupItemInfo(Texture* _itemTex, const ItemInfo& _info)
{
	mSetupItemTex = _itemTex;
	mItemNameTex = FontMgr::GetInstance().GetTextTexture(_info.mItemName, _info.mItemName);
	mItemCommentTex = FontMgr::GetInstance().GetTextTexture(_info.mItemComment, _info.mItemComment);



	std::wstring attLine = L"공격력 : " + std::to_wstring((int)(_info.mMinAtt)) + L"~" + std::to_wstring((int)(_info.mMaxAtt));
	mItemAttTex = FontMgr::GetInstance().GetTextTexture(attLine, attLine);
	mItemAttTex->ChangeColor(RGB_WHITE, RGB_YELLOW, mItemAttTex->GetWidth() - 75);

	std::wstring attSpeedLine = L"초당 공격 속도 : " + std::to_wstring((int)(_info.mAttSpeed));
	mItemAttSpeedTex = FontMgr::GetInstance().GetTextTexture(attSpeedLine, attSpeedLine);
	mItemAttSpeedTex->ChangeColor(RGB_WHITE, RGB_YELLOW, mItemAttSpeedTex->GetWidth() - 25);




	switch (_info.mWeaponType)
	{
	case WEAPON_TYPE::ONE_HAND:
		mItemWeaponTypeTex = FontMgr::GetInstance().GetTextTexture(L"한손(주무기)", L"한손(주무기)");
		mItemWeaponTypeTex->ChangeColor(RGB_WHITE, RGB_GRAY);
		break;

	case WEAPON_TYPE::TWO_HAND:
		mItemWeaponTypeTex = FontMgr::GetInstance().GetTextTexture(L"양손(주무기)", L"양손(주무기)");
		mItemWeaponTypeTex->ChangeColor(RGB_WHITE, RGB_GRAY);
		break;
	}


	if (nullptr != mItemNameTex)
	{
		COLORREF color = RGB_WHITE;
		switch (_info.mRarity)
		{
		case RARITY::NORMAL:
			break;
		case RARITY::RARE:
			color = RGB_YELLOW;
			break;
		case RARITY::UNIQUE:
			color = RGB_PHONE_MAGENTA;
			break;
		}

		mItemNameTex->ChangeColor(RGB_WHITE, color);
	}

}

void ItemInfoHUD::ItemTextureRender()
{
	Vec2 pos = GetPos();
	Vec2 baseSize = mBaseTex->GetSize();
	Vec2 infoBaseSize = mInfoBase->GetSize();
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

void ItemInfoHUD::ItemNameRender()
{
	Vec2 pos = GetPos();
	Vec2 baseSize = mBaseTex->GetSize();
	Vec2 itemNameTexSize = mItemNameTex->GetSize();
	TransparentBlt(
		BACK_BUF_DC,
		(int)(pos.x - baseSize.x / 2.f - itemNameTexSize.x / 2.f),
		(int)(pos.y - itemNameTexSize.y / 2.f + 20.f),
		(int)itemNameTexSize.x,
		(int)itemNameTexSize.y,
		mItemNameTex->GetDC(),
		0, 0,
		(int)itemNameTexSize.x,
		(int)itemNameTexSize.y,
		RGB(255, 0, 255)
	);
}

void ItemInfoHUD::ItemCommentRender()
{
	Vec2 pos = GetPos();
	Vec2 baseSize = mBaseTex->GetSize();
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
		(int)itemCommentTexOrgSize.x,
		(int)itemCommentTexOrgSize.y,
		RGB(255, 0, 255)
	);
}

void ItemInfoHUD::ItemAttackValueRender()
{
	Vec2 pos = GetPos();
	Vec2 baseSize = mBaseTex->GetSize();
	Vec2 itemAttTexOrgSize = mItemAttTex->GetSize();
	Vec2 itemAttTexSize = (itemAttTexOrgSize / 5.f) * 4.f;

	TransparentBlt(
		BACK_BUF_DC,
		(int)(pos.x - baseSize.x / 2.f - 30.f),
		(int)(pos.y - itemAttTexSize.y / 2.f + 75.f),
		(int)itemAttTexSize.x,
		(int)itemAttTexSize.y,
		mItemAttTex->GetDC(),
		0, 0,
		(int)itemAttTexOrgSize.x,
		(int)itemAttTexOrgSize.y,
		RGB(255, 0, 255)
	);
}

void ItemInfoHUD::ItemAttackSpeedRender()
{
	Vec2 pos = GetPos();
	Vec2 baseSize = mBaseTex->GetSize();
	Vec2 itemAttSpeedTexOrgSize = mItemAttSpeedTex->GetSize();
	Vec2 itemAttSpeedTexSize = (itemAttSpeedTexOrgSize / 5.f) * 4.f;

	TransparentBlt(
		BACK_BUF_DC,
		(int)(pos.x - baseSize.x / 2.f - 30.f),
		(int)(pos.y - itemAttSpeedTexSize.y / 2.f + 100.f),
		(int)itemAttSpeedTexSize.x,
		(int)itemAttSpeedTexSize.y,
		mItemAttSpeedTex->GetDC(),
		0, 0,
		(int)itemAttSpeedTexOrgSize.x,
		(int)itemAttSpeedTexOrgSize.y,
		RGB(255, 0, 255)
	);
}

void ItemInfoHUD::ItemWeaponTypeRender()
{
	Vec2 pos = GetPos();
	Vec2 baseSize = mBaseTex->GetSize();
	Vec2 itemWeaponTypeTexOrgSize = mItemWeaponTypeTex->GetSize();
	Vec2 itemWeaponTypeTexSize = (itemWeaponTypeTexOrgSize / 5.f) * 4.f;

	TransparentBlt(
		BACK_BUF_DC,
		(int)(pos.x - baseSize.x + 10.f),
		(int)(pos.y - itemWeaponTypeTexSize.y / 2.f + 170.f),
		(int)itemWeaponTypeTexSize.x,
		(int)itemWeaponTypeTexSize.y,
		mItemWeaponTypeTex->GetDC(),
		0, 0,
		(int)itemWeaponTypeTexOrgSize.x,
		(int)itemWeaponTypeTexOrgSize.y,
		RGB(255, 0, 255)
	);
}

void ItemInfoHUD::Destroy()
{
	HUD::Destroy();
}
