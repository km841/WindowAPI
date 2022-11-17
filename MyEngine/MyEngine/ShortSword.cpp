#include "pch.h"
#include "ShortSword.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Player.h"
#include "TimeMgr.h"
#include "CameraMgr.h"

ShortSword::ShortSword()
{
	SetOffset(Vec2(70.f, -2.f));
	SetItemType(ITEM_TYPE::WEAPON_1);
}

ShortSword::~ShortSword()
{
}

void ShortSword::Initialize()
{
	Texture* texture = ResourceMgr::GetInstance().Load<Texture>(L"ShortSword", L"Texture\\ShortSword3.bmp");
	Texture* transTexture = ResourceMgr::GetInstance().CreateTexture(L"ShortSwordTrans", texture->GetSize());
	
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

void ShortSword::Update()
{

	// shortsword의 pos
	// pos.x - size.x, pos.y - size.y가 좌상단
	// pos.x + size.x, pos.y - size.y가 우상단
	// pos.x - size.x, pos.y + size.y가 좌하단

	// 10도 올라간 칼의 위치는?
	// (xcos10' - ysin10'), (xsin10' + ycos10')

	// pos를 정하는건? 플레이어 기준 offset
	Sword::Update();
}

void ShortSword::Render()
{
	Sword::Render();
}
