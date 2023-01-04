#include "pch.h"
#include "LaraMagicWand.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Player.h"
#include "PlayerEffect.h"
#include "CameraMgr.h"
#include "KeyMgr.h"
#include "MouseMgr.h"
#include "HomingMissileEffect.h"
#include "RigidBody.h"

LaraMagicWand::LaraMagicWand()
	: mSkillCoolDown(3.f)
	, mCurCoolDown(0.f)
	, mEquipTex(nullptr)
	, mSkillTex(nullptr)
	, mCoolSkillTex(nullptr)
	, mSound(nullptr)
{
	SetType(OBJECT_TYPE::DROP_ITEM);
	SetOffset(Vec2(40.f, -2.f));
	SetItemType(ITEM_TYPE::WEAPON);
	SetLeftDirOffset(8.f);
	SetRightDirOffset(41.f);
	SetYOffset(8.f);
	SetDuration(0.225f);

	ItemInfo info = {};
	info.mMinAtt = 10.f;
	info.mMaxAtt = 15.f;
	info.mAttSpeed = 4.f;
	info.mMaxAmmo = 12.f;
	info.mAmmo = info.mMaxAmmo;
	info.mItemName = L"라라의 요술봉";
	info.mItemComment = L"'마법 소녀 라라가 잃어버린 요술봉'";
	info.mRarity = RARITY::UNIQUE;
	info.mWeaponType = WEAPON_TYPE::ONE_HAND;
	SetItemInfo(info);

	Texture* texture = LOAD_TEXTURE(L"LaraMagicWandTex", L"Texture\\LalaMagicWand.bmp");
	mEquipTex = LOAD_TEXTURE(L"LaraMagicWandEquipTex", L"Texture\\LalaMagicWandEquip.bmp");
	Texture* transTexture = ResourceMgr::GetInstance().CreateTexture(L"LaraMagicWandTrans", texture->GetSize());


	SetTexture(texture);
	SetTransTexture(transTexture);
	SetEquipedTexture(mEquipTex);

	mSkillTex = LOAD_TEXTURE(L"LaraSkillTex", L"Texture\\LaraSkill.bmp");
	mCoolSkillTex = LOAD_TEXTURE(L"LaraCoolSkillTex", L"Texture\\LaraSkillDisable.bmp");

	HomingMissileEffect* effect = new HomingMissileEffect;
	effect->SetOwner(Player::GetPlayer());
	effect->SetAtt(info.mMinAtt, info.mMaxAtt);
	effect->SetOwnerItem(this);
	SetEffect(effect);
	
	mSkillCoolDown = 3.f;
}

LaraMagicWand::~LaraMagicWand()
{
	Weapon::Destroy();
}

void LaraMagicWand::Initialize()
{
	// 먹은 다음에 Initialize

	Weapon::Initialize();

	Player* player = Player::GetPlayer();
	if (nullptr != player)
	{
		Vec2 playerPos = player->GetPos();
		SetPos(playerPos + GetOffset());
	}

	SetSize(GetTexture()->GetSize());
}

void LaraMagicWand::Update()
{

	if (mHasFallen)
	{
		GameObject::Update();
	}

	else
	{
		SetPrevSwordState(GetSwordState());

		if (IS_JUST_LBUTTON_CLICKED)
		{
			ChangeSwordState();


			// Effect 처리

		}


		if (GetPrevSwordState() != GetSwordState())
		{

			Vec2 dirVec = { 1.f, 0.f };


			float angle = GetAngle();
			float degree = Math::RadianToDegree(angle);

			//wchar_t buf[256] = {};
			//swprintf_s(buf, L"%f", degree);
			//SetWindowText(APP_INSTANCE.GetHwnd(), buf);


			Player* player = Player::GetPlayer();
			DIR playerDir = player->GetPlayerDir();
			Vec2 basicOffset = {};

			switch (playerDir)
			{
			case DIR::LEFT:
				basicOffset = Vec2(-25.f, -15.f);
				break;

			case DIR::RIGHT:
				basicOffset = Vec2(25.f, -15.f);
				break;
			}

			//GetEffect()->SetAngle(angle);
			//GetEffect()->SetOffset(basicOffset * 30.f);
		}

		if (nullptr != mEffect)
		{
			// Effect의 Update에서 총알의 위치를 세팅해줌
			mEffect->Update();
		}

		Weapon::Update();
	}

}

void LaraMagicWand::Render()
{
	if (mHasFallen)
	{
		Vec2 pos = RENDER_POS(GetPos());
		Vec2 size = mEquipTex->GetSize();
		
		TransparentBlt(
			BACK_BUF_DC,
			(int)(pos.x - size.x / 2.f),
			(int)(pos.y - size.y / 2.f),
			(int)(size.x),
			(int)(size.y),
			mEquipTex->GetDC(),
			0, 0,
			(int)size.x,
			(int)size.y,
			RGB(255, 0, 255)
		);

		GameObject::Render();
	}

	else
	{
		Weapon::Render();

		Vec2 pos = Vec2(WINDOW_WIDTH_SIZE - 200, WINDOW_HEIGHT_SIZE - 50);
		Vec2 size = mSkillTex->GetSize();

		if (mCoolDown)
		{
			TransparentBlt(
				BACK_BUF_DC,
				(int)(pos.x - size.x / 2.f),
				(int)(pos.y - size.y / 2.f),
				(int)(size.x),
				(int)(size.y),
				mCoolSkillTex->GetDC(),
				0, 0,
				(int)size.x,
				(int)size.y,
				RGB(255, 0, 255)
			);
		}

		else
		{
			TransparentBlt(
				BACK_BUF_DC,
				(int)(pos.x - size.x / 2.f),
				(int)(pos.y - size.y / 2.f),
				(int)(size.x),
				(int)(size.y),
				mSkillTex->GetDC(),
				0, 0,
				(int)size.x,
				(int)size.y,
				RGB(255, 0, 255)
			);
		}


		if (nullptr != mEffect)
		{
			mEffect->Render();
		}
	}
	

}

void LaraMagicWand::Destroy()
{
	
}

void LaraMagicWand::Change()
{
	mEffect->Change();
}
