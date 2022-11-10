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
#include "IdleState.h"
#include "WalkState.h"
#include "GameObject.h"

IdleState* PlayerState::Idle = nullptr;
WalkState* PlayerState::Walk = nullptr;

Player::Player()
{
	PlayerState::Idle = new IdleState(this);
	PlayerState::Walk = new WalkState(this);

	SetType(OBJECT_TYPE::PLAYER);
	SetSize(Vec2(96.f, 96.f));

	mDefaultTexture = ResourceMgr::GetInstance().Load<Texture>(L"PLAYER_ANIMATION", L"Texture\\player_animation.bmp");
	Texture* mDust = ResourceMgr::GetInstance().Load<Texture>(L"PLAYER_DUST", L"Texture\\player_dust.bmp");


	CreateComponent(new Collider);
	GetCollider()->SetOwner(this);

	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	GetAnimator()->AddAnimation(L"PLAYER_IDLE_LEFT", 
		GetAnimator()->CreateAnimation(L"PLAYER_IDLE_LEFT", mDefaultTexture, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 5, true));

	GetAnimator()->AddAnimation(L"PLAYER_IDLE_RIGHT",
		GetAnimator()->CreateAnimation(L"PLAYER_IDLE_RIGHT", mDefaultTexture, Vec2(0.f, 32.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 5, true));

	GetAnimator()->AddAnimation(L"PLAYER_WALK_LEFT",
		GetAnimator()->CreateAnimation(L"PLAYER_WALK_LEFT", mDefaultTexture, Vec2(0.f, 64.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.05f, 8, true));

	GetAnimator()->AddAnimation(L"PLAYER_WALK_RIGHT",
		GetAnimator()->CreateAnimation(L"PLAYER_WALK_RIGHT", mDefaultTexture, Vec2(0.f, 96.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.05f, 8, true));

	Animation* leftDust = GetAnimator()->CreateAnimation(L"PLAYER_DUST_LEFT", mDust, Vec2(0.f, 0.f), Vec2(16.f, 16.f), Vec2(16.f, 0.f), 0.05f, 6, false);
	Animation* rightDust = GetAnimator()->CreateAnimation(L"PLAYER_DUST_RIGHT", mDust, Vec2(0.f, 16.f), Vec2(16.f, 16.f), Vec2(16.f, 0.f), 0.05f, 6, false);

	Animation* leftWalk = GetAnimator()->FindAnimation(L"PLAYER_WALK_LEFT");
	leftWalk->SetEnterEvent(Animation::EventAnimation(L"PLAYER_DUST_LEFT", rightDust, Vec2(-20.f, 0.f), Vec2(8.f, 8.f)));

	Animation* rightWalk = GetAnimator()->FindAnimation(L"PLAYER_WALK_RIGHT");
	rightWalk->SetEnterEvent(Animation::EventAnimation(L"PLAYER_DUST_RIGHT", leftDust, Vec2(20.f, 0.f), Vec2(8.f, 8.f)));
	
	GetAnimator()->SelectAnimation(L"PLAYER_IDLE_RIGHT");
}

Player::~Player()
{
	if (nullptr != PlayerState::Idle)
		delete PlayerState::Idle;

	if (nullptr != PlayerState::Walk)
		delete PlayerState::Walk;
}

void Player::Initialize()
{
	mPrevPos = GetPos();
}

void Player::Update()
{

	PlayerInput();
	if (IsMove())
	{
		if (nullptr != mState)
			mState->Exit();
		
		mState = PlayerState::Walk;
		mState->Enter();
	}

	else
	{
		if (nullptr != mState)
			mState->Exit();

		mState = PlayerState::Idle;
		mState->Enter();
	}
	
	GameObject::Update();
}

void Player::PlayerInput()
{
	Vec2 pos = GetPos();

	if (IS_PRESSED(KEY::W))
		pos.y -= (PLAYER_SPEED * DT);

	if (IS_PRESSED(KEY::S))
		pos.y += (PLAYER_SPEED * DT);

	if (IS_PRESSED(KEY::A))
		pos.x -= (PLAYER_SPEED * DT);

	if (IS_PRESSED(KEY::D))
		pos.x += (PLAYER_SPEED * DT);

	if (MOUSE_POS.x > RENDER_POS(pos).x)
		mDir = PLAYER_DIR::RIGHT;
	else
		mDir = PLAYER_DIR::LEFT;

	mPrevPos = GetPos();
	SetPos(pos);
}

bool Player::IsMove() const
{
	Vec2 pos = GetPos();
	return !((abs(mPrevPos.x - pos.x) < EPSILON) &&
		(abs(mPrevPos.y - pos.y) < EPSILON));
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




