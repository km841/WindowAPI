#include "pch.h"
#include "GreatSword.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Player.h"
#include "TimeMgr.h"
#include "CameraMgr.h"

GreatSword::GreatSword()
{
	SetOffset(Vec2(80.f, 0.f));
	SetItemType(ITEM_TYPE::WEAPON_1);
}

GreatSword::~GreatSword()
{
}

void GreatSword::Initialize()
{
	Texture* texture = ResourceMgr::GetInstance().Load<Texture>(L"GreatSword", L"Texture\\GreatSword3.bmp");
	Texture* transTexture = ResourceMgr::GetInstance().CreateTexture(L"GreatSwordTrans", texture->GetSize());


	SetTexture(texture);
	SetTransTexture(transTexture);

	Sword::Initialize();

	Player* player = Player::GetPlayer();
	if (nullptr != player)
	{
		Vec2 playerPos = player->GetPos();
		SetPos(playerPos + GetOffset());
	}

	SetSize(texture->GetSize());
}

void GreatSword::Update()
{
	Sword::Update();
}

void GreatSword::Render()
{
	Sword::Render();
}
