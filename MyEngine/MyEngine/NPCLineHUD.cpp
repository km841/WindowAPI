#include "pch.h"
#include "NPCLineHUD.h"
#include "ResourceMgr.h"
#include "Texture.h"

NPCLineHUD::NPCLineHUD()
{
	mTex = ResourceMgr::GetInstance().Load<Texture>(L"NPCLineBaseTex", L"Texture\\NPCLineBase.bmp");
	SetPos(Vec2(0, WINDOW_HEIGHT_SIZE - mTex->GetHeight()));
}

NPCLineHUD::~NPCLineHUD()
{
}

void NPCLineHUD::Initialize()
{
	HUD::Initialize();
}

void NPCLineHUD::Update()
{
	HUD::Update();
}

void NPCLineHUD::Render()
{
	HUD::Render();
	
	if (nullptr != mTex && GetState())
	{
		Vec2 size = mTex->GetSize();
		Vec2 pos = GetPos();
		TransparentBlt(
			BACK_BUF_DC,
			(int)pos.x,
			(int)pos.y,
			(int)size.x,
			(int)size.y,
			mTex->GetDC(),
			0, 0,
			(int)size.x,
			(int)size.y,
			RGB(255, 0, 255)
		);
	}

}

void NPCLineHUD::Destroy()
{
	HUD::Destroy();
}
