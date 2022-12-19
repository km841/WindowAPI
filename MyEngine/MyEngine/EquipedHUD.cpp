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
	// �� ������ ���� ����� ������ �ִ� �ڸ��� ���� �̵��ϰ�, �������� ���� �ٲ�� �׷����� ������ �ٲ�
	// �� ���� �׸��µ� �̵����� �ؾ� ��
	// ���� �׷����� ��ġ�� �־�� �Ѵ�
	// pos 2���� ���� �ְ� �� pos���� �׸��°�?
	// ��ǥ���� pos�� 2���� �ְ�,
	// cur pos�� 2���� �־�� ��
	// â�� �׷����� �����?
	// Player�� ����
	// Player -> EquipItem -> GetEquipedWeaponTexture()
	// �׸��� ����
	// 1. ���� ���̽�
	// 2. ���� ����
	// 3. ���� ���̽�
	// 4. ���� ����

	// ���� ���� : ������ �������� x - 10
	// �Ĺ� ���� : ������ �������� y - 10

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

			// n�ʰ� n�� �Ÿ��� ��
			// ���� ��� �־�� �ϴ°�?
			// ���� ��ġ - ���� ��ġ
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
		// �� ���� ����

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

		// ���� ���� ����
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
