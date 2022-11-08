#include "pch.h"
#include "Player.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "CameraMgr.h"

Player::Player()
{
	SetType(OBJECT_TYPE::PLAYER);
	SetSize(Vec2(96.f, 96.f));
	mTexture = ResourceMgr::GetInstance().Load<Texture>(L"Player_IDLE", L"Texture\\idle.bmp");
	assert(nullptr != mTexture);
	
	CreateComponent(new Collider);
	GetCollider()->SetOwner(this);

	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	GetAnimator()->CreateAnimation(L"WALK", mTexture, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 5);
	GetAnimator()->SelectAnimation(L"WALK");
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
