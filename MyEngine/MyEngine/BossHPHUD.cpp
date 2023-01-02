#include "pch.h"
#include "BossHPHUD.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "BossMonster.h"

BossHPHUD::BossHPHUD()
{
	mBaseTex = LOAD_TEXTURE(L"BossHPBaseTex", L"Texture\\BossHPBase.bmp");
	mTex = LOAD_TEXTURE(L"BossHPTex", L"Texture\\BossHP.bmp");

	SetPos(Vec2(WINDOW_WIDTH_SIZE / 2, WINDOW_HEIGHT_SIZE - 50));
}

BossHPHUD::~BossHPHUD()
{
}

void BossHPHUD::Initialize()
{
	HUD::Initialize();
}

void BossHPHUD::Update()
{
	HUD::Update();
}

void BossHPHUD::Render()
{
	if (GetState() && 
		nullptr != mTex && nullptr != mBaseTex)
	{
		HUD::Render();

		Vec2 hpBaseSize = mBaseTex->GetSize();
		Vec2 hpSize = mTex->GetSize();
		Vec2 pos = GetPos();

		Vec2 basePos = pos - hpBaseSize / 2.f;
		TransparentBlt(
			BACK_BUF_DC,
			(int)basePos.x,
			(int)basePos.y,
			(int)hpBaseSize.x,
			(int)hpBaseSize.y,
			mBaseTex->GetDC(),
			0, 0,
			(int)hpBaseSize.x,
			(int)hpBaseSize.y,
			RGB(255, 0, 255)
		);

		Vec2 hpBarPos = basePos;
		hpBarPos.x += 100;
		hpBarPos.y += 14;

		MonsterInfo info =mBoss->GetMonsterInfo();
		float ratio = info.mCurHP / info.mMaxHP;

		TransparentBlt(
			BACK_BUF_DC,
			(int)(hpBarPos.x),
			(int)(hpBarPos.y),
			(int)(hpSize.x * ratio),
			(int)(hpSize.y),
			mTex->GetDC(),
			0, 0,
			(int)(hpSize.x * ratio),
			(int)(hpSize.y),
			RGB(255, 0, 255)
		);
	}
}

void BossHPHUD::Destroy()
{
}
