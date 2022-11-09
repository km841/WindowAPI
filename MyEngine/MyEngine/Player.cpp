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

	mTextureMap.insert(
		std::make_pair(L"PLAYER_IDLE_LEFT", (ResourceMgr::GetInstance().Load<Texture>(L"PLAYER_IDLE_LEFT", L"Texture\\idle_left.bmp"))));

	mTextureMap.insert(
		std::make_pair(L"PLAYER_IDLE_RIGHT", (ResourceMgr::GetInstance().Load<Texture>(L"PLAYER_IDLE_RIGHT", L"Texture\\idle_right.bmp"))));

	mTextureMap.insert(
		std::make_pair(L"PLAYER_WALK_LEFT", (ResourceMgr::GetInstance().Load<Texture>(L"PLAYER_WALK_LEFT", L"Texture\\walk_left.bmp"))));

	mTextureMap.insert(
		std::make_pair(L"PLAYER_WALK_RIGHT", (ResourceMgr::GetInstance().Load<Texture>(L"PLAYER_WALK_RIGHT", L"Texture\\walk_right.bmp"))));
	
	CreateComponent(new Collider);
	GetCollider()->SetOwner(this);

	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	GetAnimator()->CreateAnimation(L"PLAYER_IDLE_LEFT", GetTexture(L"PLAYER_IDLE_LEFT"), Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"PLAYER_IDLE_RIGHT", GetTexture(L"PLAYER_IDLE_RIGHT"), Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"PLAYER_WALK_LEFT", GetTexture(L"PLAYER_WALK_LEFT"), Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 8);
	GetAnimator()->CreateAnimation(L"PLAYER_WALK_RIGHT", GetTexture(L"PLAYER_WALK_RIGHT"), Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 8);

	GetAnimator()->SelectAnimation(L"PLAYER_IDLE_RIGHT");
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

	if (IS_JUST_PRESSED(KEY::LEFT))
	{
		SelectTexture(L"PLAYER_WALK_LEFT");
		GetAnimator()->SelectAnimation(L"PLAYER_WALK_LEFT");
	}

	if (IS_JUST_PRESSED(KEY::RIGHT))
	{
		SelectTexture(L"PLAYER_WALK_RIGHT");
		GetAnimator()->SelectAnimation(L"PLAYER_WALK_RIGHT");
	}

	if (IS_JUST_RELEASED(KEY::LEFT))
	{
		SelectTexture(L"PLAYER_IDLE_LEFT");
		GetAnimator()->SelectAnimation(L"PLAYER_IDLE_LEFT");
	}


	if (IS_JUST_RELEASED(KEY::RIGHT))
	{
		SelectTexture(L"PLAYER_IDLE_RIGHT");
		GetAnimator()->SelectAnimation(L"PLAYER_IDLE_RIGHT");
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

Texture* Player::GetTexture(const std::wstring& _key)
{
	std::map<std::wstring, Texture*>::iterator iter = mTextureMap.find(_key);
	if (iter != mTextureMap.end())
	{
		return iter->second;
	}
	return nullptr;
}

void Player::SelectTexture(const std::wstring& _key)
{
	mCurTexture = GetTexture(_key);
}
