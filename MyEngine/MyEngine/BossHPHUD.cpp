#include "pch.h"
#include "BossHPHUD.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "BossMonster.h"

BossHPHUD::BossHPHUD()
{
	mBaseTex = ResourceMgr::GetInstance().Load<Texture>(L"BossHPBaseTex", L"Texture\\BossHPBase.bmp");
	mTex = ResourceMgr::GetInstance().Load<Texture>(L"BossHPTex", L"Texture\\BossHP.bmp");

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
			basePos.x,
			basePos.y,
			hpBaseSize.x,
			hpBaseSize.y,
			mBaseTex->GetDC(),
			0, 0,
			hpBaseSize.x,
			hpBaseSize.y,
			RGB(255, 0, 255)
		);

		Vec2 hpBarPos = basePos;
		hpBarPos.x += 100;
		hpBarPos.y += 14;

		MonsterInfo info =mBoss->GetMonsterInfo();
		float ratio = info.mCurHP / info.mMaxHP;


		TransparentBlt(
			BACK_BUF_DC,
			hpBarPos.x,
			hpBarPos.y,
			hpSize.x * ratio,
			hpSize.y,
			mTex->GetDC(),
			0, 0,
			hpSize.x * ratio,
			hpSize.y,
			RGB(255, 0, 255)
		);
	}
}

void BossHPHUD::Destroy()
{
}
