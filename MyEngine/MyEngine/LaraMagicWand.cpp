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

LaraMagicWand::LaraMagicWand()
{
	SetOffset(Vec2(40.f, -2.f));
	SetItemType(ITEM_TYPE::WEAPON);
	SetLeftDirOffset(8.f);
	SetRightDirOffset(41.f);
	SetYOffset(8.f);
	SetDuration(0.225f);

	ItemInfo info = {};
	info.mAtt = 10.f;
	SetItemInfo(info);

	Texture* texture = ResourceMgr::GetInstance().Load<Texture>(L"ShortSword", L"Texture\\LalaMagicWand.bmp");
	Texture* transTexture = ResourceMgr::GetInstance().CreateTexture(L"ShortSwordTrans", texture->GetSize());
	SetTexture(texture);
	SetTransTexture(transTexture);

	HomingMissileEffect* effect = new HomingMissileEffect;
	effect->SetOwner(Player::GetPlayer());
	effect->SetAtt(info.mAtt);
	SetEffect(effect);
	
}

LaraMagicWand::~LaraMagicWand()
{
}

void LaraMagicWand::Initialize()
{
	Sword::Initialize();

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

	Sword::Update();
}

void LaraMagicWand::Render()
{
	Sword::Render();
}

void LaraMagicWand::Destroy()
{
	Sword::Destroy();
}
