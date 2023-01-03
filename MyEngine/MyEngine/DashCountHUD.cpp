#include "pch.h"
#include "DashCountHUD.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Player.h"

DashCountHUD::DashCountHUD()
{
	mBaseTex = LOAD_TEXTURE(L"DashCountBaseTex", L"Texture\\DashCountBase.bmp");
	mTex = LOAD_TEXTURE(L"DashCountTex", L"Texture\\DashCount.bmp");

	SetPos(Vec2(10, 65));
}

DashCountHUD::~DashCountHUD()
{
}

void DashCountHUD::Initialize()
{
	HUD::Initialize();
}

void DashCountHUD::Update()
{
	HUD::Update();
}

void DashCountHUD::Render()
{
	if (false == GetState())
		return;

	if (nullptr != mBaseTex && nullptr != mTex)
	{
		Player* player = Player::GetPlayer();
		if (nullptr != player)
		{
			Vec2 dashBaseSize = mBaseTex->GetSize();
			Vec2 dashSize = mTex->GetSize();
			Vec2 pos = GetPos();

			PlayerInfo info = player->GetPlayerInfo();
			float dashCount = info.mDashCount;

			TransparentBlt(
				BACK_BUF_DC,
				(int)pos.x,
				(int)pos.y,
				(int)dashBaseSize.x,
				(int)dashBaseSize.y,
				mBaseTex->GetDC(),
				0, 0,
				(int)dashBaseSize.x,
				(int)dashBaseSize.y,
				RGB(255, 0, 255)
			);

			for (int i = 0; i < dashCount; ++i)
			{
				// 6x6
				// 다음거는 3띄우고
				TransparentBlt(
					BACK_BUF_DC,
					(int)(pos.x + 6 + (i * (dashSize.x + 3))),
					(int)(pos.y + 6),
					(int)dashSize.x,
					(int)dashSize.y,
					mTex->GetDC(),
					0, 0,
					(int)(dashSize.x),
					(int)dashSize.y,
					RGB(255, 0, 255)
				);
			}
		}
	}

	HUD::Render();
}

void DashCountHUD::Destroy()
{
	HUD::Destroy();
}
