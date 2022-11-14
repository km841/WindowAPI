#include "pch.h"
#include "Structure.h"
#include "CameraMgr.h"
#include "Texture.h"

Structure::Structure()
	: mTexture(nullptr)
{
	SetType(OBJECT_TYPE::STRUCTURE);
}

Structure::~Structure()
{
}

void Structure::Initialize()
{
}

void Structure::Update()
{
	GameObject::Update();
}

void Structure::Render()
{
	if (nullptr != mTexture)
	{
		Vec2 pos = GetPos();
		Vec2 size = GetSize();

		// Convert Render Pos
		pos = RENDER_POS(pos);

		TransparentBlt(BACK_BUF_DC
			, (int)(pos.x - size.x / 2.f)
			, (int)(pos.y - size.y)
			, (int)(size.x)
			, (int)(size.y)
			, mTexture->GetDC()
			, 0, 0
			, mTexture->GetWidth()
			, mTexture->GetHeight()
			, RGB(255, 0, 255)
		);
	}

	GameObject::Render();
}

void Structure::Destroy()
{
}

void Structure::OnCollision(Collider* _other)
{
}

void Structure::OnCollisionEnter(Collider* _other)
{
}

void Structure::OnCollisionExit(Collider* _other)
{
}
