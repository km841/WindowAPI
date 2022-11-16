#include "pch.h"
#include "ShortSword.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Player.h"
#include "TimeMgr.h"
#include "CameraMgr.h"

ShortSword::ShortSword()
{
	SetOffset(Vec2(60.f, -10.f));
	SetItemType(ITEM_TYPE::WEAPON_1);
}

ShortSword::~ShortSword()
{
}

void ShortSword::Initialize()
{
	Texture* texture = ResourceMgr::GetInstance().Load<Texture>(L"ShortSword", L"Texture\\ShortSword.bmp");
	Texture* transTexture = ResourceMgr::GetInstance().CreateTexture(L"ShortSwordTrans", texture->GetSize());
	SetTexture(texture);
	SetTransTexture(transTexture);

	Player* player = Player::GetPlayer();
	if (nullptr != player)
	{
		Vec2 playerPos = player->GetPos();
		SetPos(playerPos + GetOffset());
	}

	SetSize(texture->GetSize() * TIMES);
}

void ShortSword::Update()
{

	// shortsword의 pos
	// pos.x - size.x, pos.y - size.y가 좌상단
	// pos.x + size.x, pos.y - size.y가 우상단
	// pos.x - size.x, pos.y + size.y가 좌하단

	// pos를 정하는건? 플레이어 기준 offset
	Player* player = Player::GetPlayer();

	if (nullptr != player) {

		Texture* tex = GetTexture();
		Vec2 playerPos = player->GetPos();
		Vec2 offset = GetOffset();

		Vec2 leftTop = Vec2(0.f, 0.f);
		Vec2 rightTop = Vec2(tex->GetSize().x, 0.f);
		Vec2 leftBtm = Vec2(0.f, tex->GetSize().x);

		SetLeftTopVertex(leftTop);
		SetRightTopVertex(rightTop);
		SetLeftBottomVertex(leftBtm);

		SetPos(playerPos + offset);
	}
}

void ShortSword::Render()
{
	Texture* tex = GetTexture();
	Texture* transTex = GetTransTexture();
	Vec2 size = GetSize();

	if (nullptr != tex && nullptr != transTex)
	{
		POINT points[(UINT)VERTICES_POINT::END] = {
			GetLeftTopVertex(),
			GetRightTopVertex(),
			GetLeftBottomVertex()
		};

		PlgBlt(
			transTex->GetDC(),
			points,
			tex->GetDC(),
			0, 0,
			(int)transTex->GetSize().x,
			(int)transTex->GetSize().y,
			NULL,
			0, 0
		);
		Vec2 pos = RENDER_POS(GetPos());
		TransparentBlt(
			BACK_BUF_DC,
			(int)(pos.x - size.x),
			(int)(pos.y - size.y),
			(int)size.x,
			(int)size.y,
			transTex->GetDC(),
			0, 0,
			(int)transTex->GetSize().x,
			(int)transTex->GetSize().y,
			RGB(255, 0, 255)
		);
	}
}
