#include "pch.h"
#include "GreatSword.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Player.h"
#include "TimeMgr.h"
#include "CameraMgr.h"

GreatSword::GreatSword()
{
	SetOffset(Vec2(40.f, -2.f));
	SetItemType(ITEM_TYPE::WEAPON);
}

GreatSword::~GreatSword()
{
}

void GreatSword::Initialize()
{
	Texture* texture = LOAD_TEXTURE(L"GreatSword", L"Texture\\GreatSword3.bmp");
	Texture* transTexture = ResourceMgr::GetInstance().CreateTexture(L"GreatSwordTrans", texture->GetSize());


	SetTexture(texture);
	SetTransTexture(transTexture);

	Weapon::Initialize();

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
	Weapon::Update();
}

void GreatSword::Render()
{
	Weapon::Render();
}
