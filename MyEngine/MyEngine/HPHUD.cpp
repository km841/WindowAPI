#include "pch.h"
#include "HPHUD.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Player.h"

HPHUD::HPHUD()
{
	mBaseTex = ResourceMgr::GetInstance().Load<Texture>(L"PlayerHPBaseTex", L"Texture\\PlayerHPBase.bmp");
	mTex = ResourceMgr::GetInstance().Load<Texture>(L"PlayerHPTex", L"Texture\\PlayerHP.bmp");

	SetPos(Vec2(10, 10));
}

HPHUD::~HPHUD()
{
}

void HPHUD::Initialize()
{
	HUD::Initialize();
}

void HPHUD::Update()
{
	HUD::Update();
}

void HPHUD::Render()
{
	if (nullptr != mBaseTex && nullptr != mTex)
	{
		Player* player = Player::GetPlayer();
		if (nullptr != player)
		{
			Vec2 hpBaseSize = mBaseTex->GetSize();
			Vec2 hpSize = mTex->GetSize();
			Vec2 pos = GetPos();

			PlayerInfo info = player->GetPlayerInfo();
			


			TransparentBlt(
				BACK_BUF_DC,
				(int)pos.x,
				(int)pos.y,
				(int)hpBaseSize.x,
				(int)hpBaseSize.y,
				mBaseTex->GetDC(),
				0, 0,
				(int)hpBaseSize.x,
				(int)hpBaseSize.y,
				RGB(255, 0, 255)
			);

			// 가로는 66 세로는 9

			float ratio = info.mCurHP / info.mMaxHP;

			TransparentBlt(
				BACK_BUF_DC,
				(int)(pos.x + 66),
				(int)(pos.y + 10),
				(int)(hpSize.x * ratio),
				(int)(hpSize.y),
				mTex->GetDC(),
				0, 0,
				(int)(hpSize.x * ratio),
				(int)hpSize.y,
				RGB(255, 0, 255)
			);
		}
	}


	HUD::Render();
}

void HPHUD::Destroy()
{
	HUD::Destroy();
}
