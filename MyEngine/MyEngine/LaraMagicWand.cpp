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

	Texture* texture = ResourceMgr::GetInstance().Load<Texture>(L"LaraMagicWandTex", L"Texture\\LalaMagicWand.bmp");
	Texture* equipedTex = ResourceMgr::GetInstance().Load<Texture>(L"LaraMagicWandEquipTex", L"Texture\\LalaMagicWandEquip.bmp");
	Texture* transTexture = ResourceMgr::GetInstance().CreateTexture(L"LaraMagicWandTrans", texture->GetSize());
	SetTexture(texture);
	SetTransTexture(transTexture);
	SetEquipedTexture(equipedTex);

	mSkillTex = ResourceMgr::GetInstance().Load<Texture>(L"LaraSkillTex", L"Texture\\LaraSkill.bmp");

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

	Vec2 pos = Vec2(WINDOW_WIDTH_SIZE - 200, WINDOW_HEIGHT_SIZE - 50);
	Vec2 size = mSkillTex->GetSize();
	
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

void LaraMagicWand::Destroy()
{
	Sword::Destroy();
}

void LaraMagicWand::Change()
{
	mEffect->Change();
}
