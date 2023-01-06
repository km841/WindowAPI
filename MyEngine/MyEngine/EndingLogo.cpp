#include "pch.h"
#include "EndingLogo.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "FontMgr.h"

EndingLogo::EndingLogo()
{
	mTex = LOAD_TEXTURE(L"mainLogo", L"Texture\\Logo.bmp");
	mThanksMessage = FontMgr::GetInstance().GetTextTexture(L"ThanksMessage", L"Thank you for playing!");
}

EndingLogo::~EndingLogo()
{
}

void EndingLogo::Initialize()
{
	GameObject::Initialize();
}

void EndingLogo::Update()
{
	GameObject::Update();
}

void EndingLogo::Render()
{
	GameObject::Render();

	if (nullptr != mTex)
	{
		Vec2 curPos = GetPos();
		Vec2 size = mTex->GetSize();
		TransparentBlt(
			BACK_BUF_DC,
			(int)curPos.x,
			(int)curPos.y,
			(int)size.x,
			(int)size.y,
			mTex->GetDC(),
			0, 0,
			(int)size.x,
			(int)size.y,
			RGB_MAGENTA
		);
	}
}

void EndingLogo::Destroy()
{
	GameObject::Destroy();
}
