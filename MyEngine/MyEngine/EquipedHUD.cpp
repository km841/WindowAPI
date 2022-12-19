#include "pch.h"
#include "EquipedHUD.h"
#include "ResourceMgr.h"
#include "Texture.h"
#include "Player.h"
#include "InventoryUI.h"
#include "UIMgr.h"
#include "Item.h"
#include "TimeMgr.h"
#include "InventoryUI.h"
#include "FontMgr.h"

EquipedHUD::EquipedHUD()
	: mChangingState(EQUIPED_CHANGING_STATE::NONE)
	, mTex(nullptr)
	, mMaxDuration(0.25f)
	, mCurDuration(0.f)
	, mDistance(0.f)
	, mVelocity(0.f)
{
	mTex = ResourceMgr::GetInstance().Load<Texture>(L"EquipedBaseTex", L"Texture\\EquippedWeaponBase.bmp");
	Vec2 pos = Vec2(WINDOW_WIDTH_SIZE - mTex->GetWidth(), WINDOW_HEIGHT_SIZE - mTex->GetHeight());
	SetPos(pos);
	// 두 슬롯이 각각 상대편 슬롯이 있던 자리를 향해 이동하고, 겹쳐지는 순간 바뀌고 그려지는 순서가 바뀜
	// 두 개를 그리는데 이동까지 해야 함
	// 각각 그려지는 위치가 있어야 한다
	// pos 2개를 갖고 있고 그 pos에다 그리는건?
	// 목표지점 pos가 2개가 있고,
	// cur pos가 2개가 있어야 함
	// 창에 그려지는 무기는?
	// Player와 교류
	// Player -> EquipItem -> GetEquipedWeaponTexture()
	// 그리는 순서
	// 1. 뒤쪽 베이스
	// 2. 뒤쪽 무기
	// 3. 앞쪽 베이스
	// 4. 앞쪽 무기

	// 전방 슬롯 : 오른쪽 구석에서 x - 10
	// 후방 슬롯 : 오른쪽 구석에서 y - 10

	mFrontSlotPos = Vec2(pos.x - 30.f, pos.y - 10);
	mFrontSlotCurPos = mFrontSlotPos;

	mBackSlotPos = Vec2(pos.x - 10, pos.y - 30.f);
	mBackSlotCurPos = mBackSlotPos;

	mDir = mFrontSlotPos - mBackSlotPos;
	mDir.Norm();

	mDistance = (mFrontSlotPos - mBackSlotPos).Len();
	mVelocity = mDistance / mMaxDuration;
}

EquipedHUD::~EquipedHUD()
{
}

void EquipedHUD::Initialize()
{
	HUD::Initialize();
}

void EquipedHUD::Update()
{
	HUD::Update();
	
	if (EQUIPED_CHANGING_STATE::CHANGING == mChangingState)
	{
		if (mMaxDuration < mCurDuration)
		{
			mChangingState = EQUIPED_CHANGING_STATE::COMPLETE;


			Player* player = Player::GetPlayer();
			if (nullptr != player->GetEquipItem(EQUIP_TYPE::WEAPON_LEFT))
			{
				player->GetEquipItem(EQUIP_TYPE::WEAPON_LEFT)->Change();
			}

			if (nullptr != player->GetEquipItem(EQUIP_TYPE::WEAPON_RIGHT))
			{
				player->GetEquipItem(EQUIP_TYPE::WEAPON_RIGHT)->Change();
			}

			GET_INVENTORY_UI->ChangeSlot();
			mCurDuration = 0.f;

			mFrontSlotCurPos = mFrontSlotPos;
			mBackSlotCurPos = mBackSlotPos;
			mDir = -mDir;
		}

		else
		{
			mCurDuration += DT;

			mFrontSlotCurPos += -mDir * (mVelocity * DT);
			mBackSlotCurPos += mDir * (mVelocity * DT);

			// n초간 n의 거리를 이
			// 내가 어디 있어야 하는가?
			// 도착 위치 - 현재 위치
		}
	}
}

void EquipedHUD::Render()
{
	if (!GetState())
		return;
	
	HUD::Render();
	Player* player = Player::GetPlayer();
	if (nullptr != mTex && player != nullptr)
	{
		InventoryUI* inven = GET_INVENTORY_UI;
		Texture* frontSlotTex = nullptr;
		Texture* backSlotTex = nullptr;

		Item* leftItem = player->GetEquipItem(EQUIP_TYPE::WEAPON_LEFT);
		Item* rightItem = player->GetEquipItem(EQUIP_TYPE::WEAPON_RIGHT);

		Item* frontSlotItem = nullptr;
		Item* backSlotItem = nullptr;

		if (INVENTORY_SLOT::LEFT_SLOT == inven->GetSlot())
		{
			if (nullptr != leftItem)
			{
				frontSlotTex = leftItem->GetEquipedTexture();
				frontSlotItem = leftItem;
			}

			if (nullptr != rightItem)
			{
				backSlotTex = rightItem->GetEquipedTexture();
				backSlotItem = rightItem;
			}
		}

		else
		{
			if (nullptr != rightItem)
			{
				frontSlotTex = rightItem->GetEquipedTexture();
				frontSlotItem = rightItem;
			}

			if (nullptr != leftItem)
			{
				backSlotTex = leftItem->GetEquipedTexture();
				backSlotItem = leftItem;
			}
		}


		Vec2 size = mTex->GetSize();
		TransparentBlt(
			BACK_BUF_DC,
			(int)mBackSlotCurPos.x,
			(int)mBackSlotCurPos.y,
			(int)size.x,
			(int)size.y,
			mTex->GetDC(),
			0, 0,
			(int)size.x,
			(int)size.y,
			RGB(255, 0, 255)
		);
		// 백 슬롯 무기

		if (nullptr != backSlotTex)
		{
			Vec2 weaponSize = backSlotTex->GetSize();
			TransparentBlt(
				BACK_BUF_DC,
				(int)((mBackSlotCurPos.x + (size.x / 2.f)) - (weaponSize.x / 2.f) - 10.f),
				(int)((mBackSlotCurPos.y + (size.y / 2.f)) - (weaponSize.y / 2.f) - 10.f),
				(int)weaponSize.x,
				(int)weaponSize.y,
				backSlotTex->GetDC(),
				0, 0,
				(int)weaponSize.x,
				(int)weaponSize.y,
				RGB(255, 0, 255)
			);
		}

		
		TransparentBlt(
			BACK_BUF_DC,
			(int)mFrontSlotCurPos.x,
			(int)mFrontSlotCurPos.y,
			(int)size.x,
			(int)size.y,
			mTex->GetDC(),
			0, 0,
			(int)size.x,
			(int)size.y,
			RGB(255, 0, 255)
		);

		// 현재 슬롯 무기
		if (nullptr != frontSlotTex)
		{
			Vec2 weaponSize = frontSlotTex->GetSize();
			TransparentBlt(
				BACK_BUF_DC,
				(int)((mFrontSlotCurPos.x + (size.x / 2.f)) - (weaponSize.x / 2.f) - 10.f),
				(int)((mFrontSlotCurPos.y + (size.y / 2.f)) - (weaponSize.y / 2.f) - 10.f),
				(int)weaponSize.x,
				(int)weaponSize.y,
				frontSlotTex->GetDC(),
				0, 0,
				(int)weaponSize.x,
				(int)weaponSize.y,
				RGB(255, 0, 255)
			);

			if (frontSlotItem->GetItemInfo().mMaxAmmo)
			{
				ItemInfo& info = frontSlotItem->GetItemInfo();
				std::wstring curAmmo = std::to_wstring((int)info.mAmmo);
				std::wstring maxAmmo = std::to_wstring((int)info.mMaxAmmo);
				std::wstring result = curAmmo + L"/" + maxAmmo;

				Texture* tex = FontMgr::GetInstance().GetTextTexture(result, result);
				
				Vec2 texSize = tex->GetSize();
				TransparentBlt(
					BACK_BUF_DC,
					(int)((mFrontSlotCurPos.x + (size.x / 2.f)) - (texSize.x / 2.f)),
					(int)((mFrontSlotCurPos.y + (size.y / 2.f)) - (texSize.y / 2.f) + 23.f),
					(int)((texSize.x / 3.f) * 2.f),
					(int)((texSize.y / 3.f) * 2.f),
					tex->GetDC(),
					0, 0,
					(int)texSize.x,
					(int)texSize.y,
					RGB(255, 0, 255)
				);

			}
		}

	}


}

void EquipedHUD::Destroy()
{
	HUD::Destroy();
}
