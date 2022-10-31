#include "pch.h"
#include "Player.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "Animator.h"

Player::Player()
{
	SetPos(Vec2{ 100.f, 700.f });
	SetScale(Vec2{ 3.f, 3.f });
	SetType(OBJECT_TYPE::PLAYER);
	mTexture = ResourceMgr::GetInstance().Load<Texture>(L"Player_Image", L"Texture\\Player.bmp");
	assert(nullptr != mTexture);
	
	CreateComponent(new Collider);
	GetCollider()->SetOwner(this);
}

Player::~Player()
{

}

void Player::Initialize()
{
	
}

void Player::Update()
{
	Vec2 pos = GetPos();
	if (IS_PRESSED(KEY::UP))
	{
		pos.y -= 600 * DT;
	}
	if (IS_PRESSED(KEY::DOWN))
	{
		pos.y += 600 * DT;
	}
	if (IS_PRESSED(KEY::LEFT))
	{
		pos.x -= 600 * DT;
	}
	if (IS_PRESSED(KEY::RIGHT))
	{
		pos.x += 600 * DT;
	}

	SetPos(pos);

	GameObject::Update();
}

void Player::Render()
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	TransparentBlt(BACK_BUF_DC
		, (int)(vPos.x - (mTexture->GetWidth() * vScale.x) / 2.f)
		, (int)(vPos.y - (mTexture->GetHeight() * vScale.y) / 2.f)
		, (int)(mTexture->GetWidth() * vScale.x)
		, (int)(mTexture->GetHeight() * vScale.y)
		, mTexture->GetDC()
		, 0, 0
		, mTexture->GetWidth()
		, mTexture->GetHeight()
		, RGB(255, 0, 255)
	);

	GameObject::Render();
}

void Player::Destroy()
{
}

void Player::OnCollision(Collider* _other)
{
}

void Player::OnCollisionEnter(Collider* _other)
{
}

void Player::OnCollisionExit(Collider* _other)
{
}
