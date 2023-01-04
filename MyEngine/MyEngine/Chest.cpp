#include "pch.h"
#include "Chest.h"
#include "Texture.h"
#include "Sound.h"
#include "ResourceMgr.h"
#include "Collider.h"
#include "CameraMgr.h"
#include "KeyMgr.h"
#include "CoinGatlingGun.h"

Chest::Chest()
	: mCollision(false)
	, mKeyTex(nullptr)
	, mOpenedTex(nullptr)
	, mClosedTex(nullptr)
	, mState(CHEST_STATE::CLOSE)
{
	SetType(OBJECT_TYPE::DUNGEON_OBJECT);

	mOpenedTex = LOAD_TEXTURE(L"ChestOpenedTex", L"Texture\\ChestOpened.bmp");
	mClosedTex = LOAD_TEXTURE(L"ChestClosedTex", L"Texture\\ChestClosed.bmp");
	mKeyTex = LOAD_TEXTURE(L"F_KEY", L"Texture\\F.bmp");

	CreateComponent(new Collider);
	GetCollider()->SetOwner(this);

	GetCollider()->SetSize(Vec2(30, 30));
	GetCollider()->SetOffset(Vec2(0, -15));
}

Chest::~Chest()
{
}

void Chest::Initialize()
{
}

void Chest::Update()
{
	GameObject::Update();

	if (CHEST_STATE::CLOSE == mState &&
		IS_JUST_PRESSED(KEY::F))
	{
		mState = CHEST_STATE::OPEN;
		// Item Drop
		CoinGatlingGun* coinGun = new CoinGatlingGun;
		Vec2 pos = GetPos();
		pos.y -= 30.f;
		coinGun->Drop(pos);
	}

}

void Chest::Render()
{
	if (nullptr != mKeyTex &&
		true == mCollision &&
		mState == CHEST_STATE::CLOSE)
	{
		Vec2 fKeyPos = GetPos();
		fKeyPos.y -= 110.f;

		fKeyPos = RENDER_POS(fKeyPos);
		Vec2 textureSize = mKeyTex->GetSize();

		TransparentBlt(
			BACK_BUF_DC,
			(int)(fKeyPos.x - ((textureSize.x * TIMES) / 2.f)),
			(int)(fKeyPos.y - ((textureSize.y * TIMES) / 2.f)),
			(int)(textureSize.x * TIMES),
			(int)(textureSize.y * TIMES),
			mKeyTex->GetDC(),
			0, 0,
			(int)textureSize.x,
			(int)textureSize.y,
			RGB(255, 0, 255)
		);
	}

	Texture* curTexture = nullptr;

	switch (mState)
	{
	case CHEST_STATE::OPEN:
		curTexture = mOpenedTex;
		break;

	case CHEST_STATE::CLOSE:
		curTexture = mClosedTex;
		break;
	}

	Vec2 curPos = RENDER_POS(GetPos());
	Vec2 size = curTexture->GetSize();
	TransparentBlt(
		BACK_BUF_DC,
		(int)(curPos.x - size.x / 2.f),
		(int)(curPos.y - size.y),
		(int)(size.x),
		(int)(size.y),
		curTexture->GetDC(),
		0, 0,
		(int)size.x,
		(int)size.y,
		RGB_MAGENTA
	);

	GameObject::Render();
}

void Chest::Destroy()
{
}

void Chest::OnCollision(Collider* _other)
{
	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		mCollision = true;
	}
}

void Chest::OnCollisionEnter(Collider* _other)
{
}

void Chest::OnCollisionExit(Collider* _other)
{
	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		mCollision = false;
	}
}
