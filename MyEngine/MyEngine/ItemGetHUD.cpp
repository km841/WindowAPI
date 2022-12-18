#include "pch.h"
#include "ItemGetHUD.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "EventRegisteror.h"
#include "TimeMgr.h"
#include "FontMgr.h"

ItemGetHUD::ItemGetHUD()
	:mMaxDuration(2.f)
	,mCurDuration(0.f)
{
	mTex = ResourceMgr::GetInstance().CreateTexture(L"ItemGetHUDTex", Vec2(300, 120));
	mTextTex = FontMgr::GetInstance().GetTextTexture(L"æ∆¿Ã≈€ »πµÊ", L"æ∆¿Ã≈€ »πµÊ");
	SetPos(Vec2(WINDOW_WIDTH_SIZE / 2.f, (WINDOW_HEIGHT_SIZE  / 2.f) + 300.f));

	mBlendFunc = {};
	mBlendFunc.BlendFlags = 0;
	mBlendFunc.AlphaFormat = 0;
	mBlendFunc.BlendOp = AC_SRC_OVER;
	mBlendFunc.SourceConstantAlpha = 127;
	
}

ItemGetHUD::~ItemGetHUD()
{
}

void ItemGetHUD::Initialize()
{
	HUD::Initialize();
}

void ItemGetHUD::Update()
{
	
	if (GetState())
	{
		HUD::Update();
		if (mMaxDuration < mCurDuration)
		{
			SetState(false);
			mCurDuration = 0.f;

			//mSetupItemTex = nullptr;
			//mItemNameTex = nullptr;
		}

		else
		{
			mCurDuration += DT;
		}
	}

}

void ItemGetHUD::Render()
{
	
	if (nullptr != mTex && GetState())
	{
		HUD::Render();
		

		Vec2 pos = GetPos();
		Vec2 HUDSize = mTex->GetSize();
		Vec2 textSize = mTextTex->GetSize();

		AlphaBlend(
			BACK_BUF_DC,
			(int)(pos.x - (HUDSize.x / 2.f)),
			(int)(pos.y - (HUDSize.y / 2.f)),
			(int)HUDSize.x,
			(int)HUDSize.y,
			mTex->GetDC(),
			0, 0,
			(int)HUDSize.x,
			(int)HUDSize.y,
			mBlendFunc
		);

		TransparentBlt(
			BACK_BUF_DC,
			(int)(pos.x - textSize.x / 2.f),
			(int)(pos.y - (HUDSize.y / 2.f) - (textSize.y / 2.f) + 20.f),
			(int)(textSize.x),
			(int)(textSize.y),
			mTextTex->GetDC(),
			0, 0,
			(int)(textSize.x),
			(int)(textSize.y),
			RGB(255, 0, 255)
		);




		if (nullptr != mSetupItemTex && nullptr != mItemNameTex)
		{
			// ¿ÃπÃ¡ˆ √‚∑¬
			Vec2 itemTexSize = mSetupItemTex->GetSize();
			Vec2 itemNameSize = mItemNameTex->GetSize();
			

			TransparentBlt(
				BACK_BUF_DC,
				(int)(pos.x - (HUDSize.x / 2.f) + 20.f),
				(int)(pos.y - (itemTexSize.y / 2.f) + 10.f),
				(int)(itemTexSize.x),
				(int)(itemTexSize.y),
				mSetupItemTex->GetDC(),
				0, 0,
				(int)itemTexSize.x,
				(int)itemTexSize.y,
				RGB(255, 0, 255)
			);

			TransparentBlt(
				BACK_BUF_DC,
				(int)(pos.x - 30.f),
				(int)(pos.y - (itemNameSize.y / 2.f) + 10.f),
				(int)(itemNameSize.x),
				(int)(itemNameSize.y),
				mItemNameTex->GetDC(),
				0, 0,
				(int)(itemNameSize.x),
				(int)(itemNameSize.y),
				RGB(255, 0, 255)
			);
			

		}
		
	}

}

void ItemGetHUD::Destroy()
{
	HUD::Destroy();
}

void ItemGetHUD::SetupItemInfo(Texture* _itemTex, const std::wstring& _itemName, RARITY _rarity)
{
	mSetupItemTex = _itemTex;
	mItemNameTex = FontMgr::GetInstance().GetTextTexture(_itemName, _itemName);

	if (nullptr != mItemNameTex)
	{
		COLORREF color = RGB(0, 0, 0);
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
