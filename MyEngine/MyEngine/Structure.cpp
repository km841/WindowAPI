#include "pch.h"
#include "Structure.h"
#include "CameraMgr.h"
#include "Texture.h"
#include "Player.h"
#include "Collider.h"
#include "State.h"
#include "IdleState.h"
#include "RigidBody.h"

Structure::Structure()
	: mTexture(nullptr)
	, mPixelTexture(nullptr)
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
