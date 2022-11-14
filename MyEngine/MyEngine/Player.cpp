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
#include "JumpState.h"
#include "GameObject.h"
#include "Effect.h"
#include "RigidBody.h"

IdleState* PlayerState::Idle = nullptr;
WalkState* PlayerState::Walk = nullptr;
JumpState* PlayerState::Jump = nullptr;

Player::Player()
	:mJumpYValue(700.f)
	,mJumpXValue(0.f)
	,mJumpXMaxValue(300.f)
	, mJumpYMinValue(0.f)
	,mFall(false)
{
	PlayerState::Idle = new IdleState(this);
	PlayerState::Walk = new WalkState(this);
	PlayerState::Jump = new JumpState(this);
	mState = PlayerState::Idle;

	SetType(OBJECT_TYPE::PLAYER);
	SetSize(Vec2(96.f, 96.f));

	mDefaultTexture = ResourceMgr::GetInstance().Load<Texture>(L"PLAYER_ANIMATION", L"Texture\\player_animation.bmp");
	Texture* dust = ResourceMgr::GetInstance().Load<Texture>(L"PLAYER_DUST", L"Texture\\player_dust.bmp");

	CreateComponent(new Collider);
	GetCollider()->SetOwner(this);

	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	CreateComponent(new RigidBody);
	GetRigidBody()->SetOwner(this);

	GetCollider()->SetSize(Vec2(30.f, 30.f));
	GetCollider()->SetOffset(Vec2(0.f, -15.f));

	Effect* effect = new Effect;
	effect->SetOwner(this);
	effect->SetSize(Vec2(48.f, 48.f));
	effect->SetOffset(Vec2(-30.f, 0.f));
	effect->CreateComponent(new Animator);
	effect->GetAnimator()->SetOwner(effect);

	Animation* dustLeft = GetAnimator()->CreateAnimation(L"PLAYER_DUST_LEFT", dust, Vec2(0.f, 0.f), Vec2(16.f, 16.f), Vec2(16.f, 0.f), 0.05f, 6);
	Animation* dustRight = GetAnimator()->CreateAnimation(L"PLAYER_DUST_RIGHT", dust, Vec2(0.f, 16.f), Vec2(16.f, 16.f), Vec2(16.f, 0.f), 0.05f, 6);

	dustLeft->SetOwner(effect->GetAnimator());
	dustRight->SetOwner(effect->GetAnimator());

	effect->GetAnimator()->AddAnimation(L"PLAYER_DUST_LEFT", dustLeft);
	effect->GetAnimator()->AddAnimation(L"PLAYER_DUST_RIGHT", dustRight);
	SetEffect(effect);

	GetAnimator()->RegisterAnimation(L"PLAYER_IDLE_LEFT", mDefaultTexture, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 5);
	GetAnimator()->RegisterAnimation(L"PLAYER_IDLE_RIGHT", mDefaultTexture, Vec2(0.f, 32.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 5);
	GetAnimator()->RegisterAnimation(L"PLAYER_WALK_LEFT", mDefaultTexture, Vec2(0.f, 64.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.05f, 8);
	GetAnimator()->RegisterAnimation(L"PLAYER_WALK_RIGHT", mDefaultTexture, Vec2(0.f, 96.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.05f, 8);
	GetAnimator()->RegisterAnimation(L"PLAYER_JUMP_LEFT", mDefaultTexture, Vec2(0.f, 128.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.2f, 1);
	GetAnimator()->RegisterAnimation(L"PLAYER_JUMP_RIGHT", mDefaultTexture, Vec2(0.f, 160.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.2f, 1);

	GetAnimator()->SelectAnimation(L"PLAYER_IDLE_RIGHT");
}

Player::~Player()
{
	if (nullptr != PlayerState::Idle)
		delete PlayerState::Idle;

	if (nullptr != PlayerState::Walk)
		delete PlayerState::Walk;

	if (nullptr != PlayerState::Jump)
		delete PlayerState::Jump;

	if (nullptr != mEffect)
		delete mEffect;
}

void Player::Initialize()
{
	mPrevPos = GetPos();
}

void Player::Update()
{
	MoveUpdate();
	EffectUpdate();

	StateUpdate();
	AnimationUpdate();

	GameObject::Update();
	mPrevState = mState;
}

void Player::MoveUpdate()
{
	Vec2 pos = GetPos();

	if (IS_PRESSED(KEY::W) || IS_PRESSED(KEY::SPACE))
	{
		// value 값을 주고 누르고있으면 떨어지는 구조, 바닥에 착지하면 초기화
		if (!mFall)
		{
			Vec2 velocity = GetRigidBody()->GetVelocity();

			if (mJumpYValue > mJumpYMinValue)
			{
				GetRigidBody()->SetVelocity(Vec2(velocity.x, -mJumpYValue));
				mJumpYValue -= 15.f;
			}

			if (mJumpYValue < mJumpYMinValue)
				mJumpYValue = mJumpYMinValue;
		}

		//if (mJumpYValue >= 700.f)
		//	mFall = true;

	}

	if (IS_JUST_RELEASED(KEY::W) || IS_JUST_RELEASED(KEY::SPACE))
	{
		if (PlayerState::Jump == mState)
			mFall = true;
	}
		//pos.y -= (PLAYER_SPEED * DT);

	if (IS_PRESSED(KEY::S))
	{

	}

	if (IS_PRESSED(KEY::A))
	{
		Vec2 velocity = GetRigidBody()->GetVelocity();

		if (PlayerState::Jump == mState)
		{
			mJumpXValue -= 50.f;
			if (-mJumpXMaxValue > mJumpXValue)
				mJumpXValue = -mJumpXMaxValue;
			
			GetRigidBody()->SetVelocity(Vec2(mJumpXValue, velocity.y));
		}
		else
			GetRigidBody()->SetVelocity(Vec2(-PLAYER_SPEED, velocity.y));
	}
		//pos.x -= (PLAYER_SPEED * DT);

	if (IS_PRESSED(KEY::D))
	{
		Vec2 velocity = GetRigidBody()->GetVelocity();

		if (PlayerState::Jump == mState)
		{
			mJumpXValue += 50.f;
			if (mJumpXMaxValue < mJumpXValue)
				mJumpXValue = mJumpXMaxValue;
				
			GetRigidBody()->SetVelocity(Vec2(mJumpXValue, velocity.y));
		}
		else
			GetRigidBody()->SetVelocity(Vec2(PLAYER_SPEED, velocity.y));
	}
		//pos.x += (PLAYER_SPEED * DT);

	mPrevDir = mDir;

	if (MOUSE_POS.x > RENDER_POS(pos).x)
		mDir = PLAYER_DIR::RIGHT;
	else
		mDir = PLAYER_DIR::LEFT;

	mPrevPos = GetPos();
	SetPos(pos);
}

void Player::EffectUpdate()
{
	Animation* anim = GetAnimator()->GetCurAnimation();
	Animation* dustRight = mEffect->GetAnimator()->FindAnimation(L"PLAYER_DUST_RIGHT");
	Animation* dustLeft = mEffect->GetAnimator()->FindAnimation(L"PLAYER_DUST_LEFT");

	if (IS_JUST_PRESSED(KEY::A) && PlayerState::Jump != mState)
	{
		dustRight->Reset();
		anim->SetCurFrame(0);
	}

	if (IS_JUST_PRESSED(KEY::D) && PlayerState::Jump != mState)
	{
		dustLeft->Reset();
		anim->SetCurFrame(0);
	}

	if (PlayerState::Walk == mState && anim->GetCurFrame() == 0)
	{
		if (IS_PRESSED(KEY::A))
		{
			
			dustRight->Reset();
			
			mEffect->SetOffset(Vec2(35.f, 0.f));
			mEffect->GetAnimator()->SelectAnimation(L"PLAYER_DUST_RIGHT", false);
		}

		if (IS_PRESSED(KEY::D))
		{
			
			dustLeft->Reset();

			mEffect->SetOffset(Vec2(-25.f, 0.f));
			mEffect->GetAnimator()->SelectAnimation(L"PLAYER_DUST_LEFT", false);
		}

		
	}

	if (nullptr != mEffect)
		mEffect->Update();
	
}

void Player::StateUpdate()
{
	if (PlayerState::Jump != mState)
	{
		if (IS_PRESSED(KEY::A) || IS_PRESSED(KEY::D))
		{
			if (nullptr != mState)
				mState->Exit();

			mState = PlayerState::Walk;
			//GetAnimator()->GetCurAnimation()->SetCurFrame(0);
			SetGravity(false);
		}

		if (IS_RELEASED(KEY::A) && IS_RELEASED(KEY::D))
		{
			if (nullptr != mState)
				mState->Exit();

			Vec2 velocity = GetRigidBody()->GetVelocity();
			GetRigidBody()->SetVelocity(Vec2(0.f, velocity.y));
			mState = PlayerState::Idle;
			//GetAnimator()->GetCurAnimation()->SetCurFrame(0);
			SetGravity(false);
		}
	}


	if (IS_RELEASED(KEY::A) && IS_RELEASED(KEY::D))
	{
		Vec2 velocity = GetRigidBody()->GetVelocity();
		GetRigidBody()->SetVelocity(Vec2(0.f, velocity.y));
	}

	if (IS_PRESSED(KEY::W) || IS_PRESSED(KEY::SPACE))
	{
		if (nullptr != mState)
			mState->Exit();

		mState = PlayerState::Jump;
		//GetAnimator()->GetCurAnimation()->SetCurFrame(0);
		SetGravity(true);
	}
	


	
}

void Player::AnimationUpdate()
{
	if ((mState != mPrevState) || (mDir != mPrevDir))
		mState->Enter();
}

bool Player::IsMove() const
{
	Vec2 pos = GetPos();
	return !((abs(mPrevPos.x - pos.x) < EPSILON) &&
		(abs(mPrevPos.y - pos.y) < EPSILON));
}

bool Player::IsLeftMove() const
{
	Vec2 pos = GetPos();
	return ((mPrevPos.x - pos.x) > EPSILON);
}

bool Player::IsRightMove() const
{
	Vec2 pos = GetPos();
	return ((pos.x - mPrevPos.x) > EPSILON);
}

bool Player::IsUpMove() const
{
	Vec2 pos = GetPos();
	return ((mPrevPos.y - pos.y) > EPSILON);
}

bool Player::IsDownMove() const
{
	Vec2 pos = GetPos();
	return ((pos.y - mPrevPos.y) > EPSILON);
}

void Player::Render()
{
	GameObject::Render();
	if (nullptr != mEffect)
		mEffect->Render();
}

void Player::Destroy()
{
}

void Player::OnCollision(Collider* _other)
{
}

void Player::OnCollisionEnter(Collider* _other)
{
	if (_other->GetOwner()->GetType() == OBJECT_TYPE::WALL)
	{
		SetGravity(false);
		mFall = false;
		Vec2 velocity = GetRigidBody()->GetVelocity();
		GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
		mState = PlayerState::Idle;
		mJumpYValue = 700.f;
		mJumpXValue = 0.f;
	}
}

void Player::OnCollisionExit(Collider* _other)
{

}




