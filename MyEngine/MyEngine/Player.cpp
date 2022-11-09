#include "pch.h"
#include "Player.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "CameraMgr.h"
#include "State.h"
#include "MouseMgr.h"
#include "Animation.h"

Player::Player()
{
	SetType(OBJECT_TYPE::PLAYER);
	SetSize(Vec2(96.f, 96.f));

	mDefaultTexture = ResourceMgr::GetInstance().Load<Texture>(L"PLAYER_ANIMATION", L"Texture\\player_animation.bmp");

	CreateComponent(new Collider);
	GetCollider()->SetOwner(this);

	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	GetAnimator()->CreateAnimation(L"PLAYER_IDLE_LEFT", mDefaultTexture, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"PLAYER_IDLE_RIGHT", mDefaultTexture, Vec2(0.f, 32.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"PLAYER_WALK_LEFT", mDefaultTexture, Vec2(0.f, 64.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 8);
	GetAnimator()->CreateAnimation(L"PLAYER_WALK_RIGHT", mDefaultTexture, Vec2(0.f, 96.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 8);
	
	GetAnimator()->SelectAnimation(L"PLAYER_IDLE_RIGHT");
}

Player::~Player()
{

}

void Player::Initialize()
{
	mPrevPos = GetPos();
}

void Player::Update()
{
	Vec2 pos = GetPos();

	if (IS_PRESSED(KEY::UP))
	{
		pos.y -= 400 * DT;
	}
	if (IS_PRESSED(KEY::DOWN))
	{
		pos.y += 400 * DT;
	}

	if (IS_PRESSED(KEY::LEFT))
	{
		pos.x -= 400.f * DT;
	}

	if (IS_PRESSED(KEY::RIGHT))
	{
		pos.x += 400.f * DT;
	}

	Vec2 mousePos = MOUSE_POS;
	Vec2 renderPos = RENDER_POS(pos);

	Animator* anim = GetAnimator();

	if (mousePos.x > renderPos.x)
	{
		mDir = PLAYER_DIR::RIGHT;
		if (L"PLAYER_IDLE_RIGHT" != anim->GetCurAnimation()->GetName())
			GetAnimator()->SelectAnimation(L"PLAYER_IDLE_RIGHT");
	}

	else
	{
		mDir = PLAYER_DIR::LEFT;
		if (L"PLAYER_IDLE_LEFT" != anim->GetCurAnimation()->GetName())
			GetAnimator()->SelectAnimation(L"PLAYER_IDLE_LEFT");
	}

	switch (mDir)
	{
	case PLAYER_DIR::LEFT:
	{
		if (abs(mPrevPos.x - pos.x) < EPSILON &&
			abs(mPrevPos.y - pos.y) < EPSILON)
		{
			if ( L"PLAYER_IDLE_LEFT" != anim->GetCurAnimation()->GetName())
				GetAnimator()->SelectAnimation(L"PLAYER_IDLE_LEFT");
		}

		else
		{
			if (L"PLAYER_WALK_LEFT" != anim->GetCurAnimation()->GetName())
				GetAnimator()->SelectAnimation(L"PLAYER_WALK_LEFT");
		}
	}
		break;

	case PLAYER_DIR::RIGHT:
	{
		if (abs(mPrevPos.x - pos.x) < EPSILON &&
			abs(mPrevPos.y - pos.y) < EPSILON)
		{
			if (L"PLAYER_IDLE_RIGHT" != anim->GetCurAnimation()->GetName())
				GetAnimator()->SelectAnimation(L"PLAYER_IDLE_RIGHT");
		}

		else
		{
			if (L"PLAYER_WALK_RIGHT" != anim->GetCurAnimation()->GetName())
				GetAnimator()->SelectAnimation(L"PLAYER_WALK_RIGHT");
		}
	}
		break;
	}

	mPrevPos = GetPos();
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
