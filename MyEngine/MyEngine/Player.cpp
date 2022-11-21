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
#include "InventoryUI.h"
#include "UIMgr.h"
#include "EventRegisteror.h"
#include "ShortSword.h"
#include "DashEffect.h"

Player* Player::mPlayer = nullptr;
IdleState* PlayerState::Idle = nullptr;
WalkState* PlayerState::Walk = nullptr;
JumpState* PlayerState::Jump = nullptr;

Player::Player()
	:mJumpYValue(700.f)
	,mJumpYMinValue(0.f)
	,mJumpXValue(0.f)
	,mJumpXMaxValue(300.f)
	,mFall(false)
	,mDashAccTime(0.f)
	,mAfterImgOffset(0.015f)
	,mDashAccMaxTime(.1f)
	,mDecTime(0.f)
	,mDecMaxTime(.08f)
	,mDecDash(false)
	,mAccDash(false)
{
	mPlayer = this;
	PlayerState::Idle = new IdleState(this);
	PlayerState::Walk = new WalkState(this);
	PlayerState::Jump = new JumpState(this);
	mState = PlayerState::Idle;

	SetType(OBJECT_TYPE::PLAYER);
	SetSize(Vec2(96.f, 96.f));

	mDefaultTexture = ResourceMgr::GetInstance().Load<Texture>(L"PLAYER_ANIMATION", L"Texture\\player_animation.bmp");
	mDashTexture = ResourceMgr::GetInstance().Load<Texture>(L"PLAYER_DASH_EFFECT", L"Texture\\player_dash_effect.bmp");
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

	DashEffect* dashEffect = new DashEffect;
	dashEffect->SetOwner(this);
	dashEffect->SetSize(Vec2(96.f, 96.f));
	dashEffect->SetOffset(Vec2(0.f, 0.f));
	dashEffect->SetTexture(mDashTexture);
	SetDashEffect(dashEffect);
	

	GetAnimator()->RegisterAnimation(L"PLAYER_IDLE_LEFT", mDefaultTexture, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 5);
	GetAnimator()->RegisterAnimation(L"PLAYER_IDLE_RIGHT", mDefaultTexture, Vec2(0.f, 32.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 5);
	GetAnimator()->RegisterAnimation(L"PLAYER_WALK_LEFT", mDefaultTexture, Vec2(0.f, 64.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.05f, 8);
	GetAnimator()->RegisterAnimation(L"PLAYER_WALK_RIGHT", mDefaultTexture, Vec2(0.f, 96.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.05f, 8);
	GetAnimator()->RegisterAnimation(L"PLAYER_JUMP_LEFT", mDefaultTexture, Vec2(0.f, 128.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.2f, 1);
	GetAnimator()->RegisterAnimation(L"PLAYER_JUMP_RIGHT", mDefaultTexture, Vec2(0.f, 160.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.2f, 1);

	GetAnimator()->SelectAnimation(L"PLAYER_IDLE_RIGHT");

	for (int i = 0; i < (UINT)ITEM_TYPE::END; ++i)
	{
		mEquipItems[i] = nullptr;
	}

	ShortSword* shortSword = new ShortSword;
	shortSword->Initialize();
	SetEquipItem(shortSword);

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

	if (nullptr != mDashEffect)
		delete mDashEffect;

	for (int i = 0; i < (UINT)ITEM_TYPE::END; ++i)
	{
		if (nullptr != mEquipItems[i])
		{
			delete mEquipItems[i];
			mEquipItems[i] = nullptr;
		}
	}

}

void Player::Initialize()
{
	mPrevPos = GetPos();
}

void Player::Update()
{
	mPrevPos = GetPos();
	GameObject::Update();
	EquipItemUpdate();
	MoveUpdate();
	EffectUpdate();

	StateUpdate();
	AnimationUpdate();

	
	mPrevState = mState;
	
}

void Player::MoveUpdate()
{
	// 감속 시간이 0이상이고 최대치보다 작은 경우
	if (mDecDash && mDecTime < mDecMaxTime)
	{
		// 현재 감속시간을 최대 감속시간으로 나눠서 1로 뺀 반대 값을 취한다.
		float ratio = 1.f - (mDecTime / mDecMaxTime);
		Vec2 curSpeed = mDashSpeed * ratio;

		GetRigidBody()->SetVelocity(curSpeed);

		mDecTime += DT;
		// 이번 증가량으로 인해 최대 감속시간이 되었다면 감속을 종료한다.
		if (mDecTime >= mDecMaxTime)
		{
			mDecTime = 0.f;
			mDecDash = false;
		}
	}

	// 가속 플래그가 켜져있고, 가속 시간이 최대 가속시간을 넘었다면
	if (mAccDash && mDashAccTime >= mDashAccMaxTime)
	{
		// 가속을 해제하고 감속을 시작한다.
		mAccDash = false;
		mDecDash = true;
		mDecTime = DT;
		mDashSpeed = GetRigidBody()->GetVelocity();
	}

	else
		mDashAccTime += DT;
	

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
	}

	if (IS_JUST_RBUTTON_CLICKED && NotInDash())
	{
		Vec2 velocity = GetRigidBody()->GetVelocity();

		Vec2 mousePos = MOUSE_POS;
		Vec2 pos = RENDER_POS(GetPos());
		Vec2 dashDir = mousePos - pos;
		dashDir.Norm();

		GetRigidBody()->SetVelocity(dashDir * PLAYER_DASH_SPEED);
		SetGround(false);
		mAccDash = true;
		mFall = true;
		mDashAccTime = 0.f;
		mDashSpeed = Vec2(dashDir * PLAYER_DASH_SPEED);
		mDashEffect->Reset();
	}

	if (IS_JUST_RELEASED(KEY::W) || IS_JUST_RELEASED(KEY::SPACE))
	{
		if (PlayerState::Jump == mState)
			mFall = true;
	}

	if (IS_PRESSED(KEY::S))
	{

	}

	if (IS_PRESSED(KEY::A))
	{
		Vec2 velocity = GetRigidBody()->GetVelocity();

		if (PlayerState::Jump == mState)
		{
			// 반대쪽으로 힘이 작용하고 있을 때 일정량 보정하고 뒤집어준다
			if (velocity.x > 0.f && NotInDash())
				GetRigidBody()->SetVelocity(Vec2(-velocity.x / 1.5f, velocity.y));

			// 현재 X방향 속도가 최대치에 도달하지 않은 경우 값 증가
			if (-mJumpXMaxValue < GetRigidBody()->GetVelocity().x)
				GetRigidBody()->AddVelocity(Vec2(-5.f, 0.f));
		}
		else
		{
			if (NotInDash())
				GetRigidBody()->SetVelocity(Vec2(-PLAYER_SPEED, velocity.y));
		}
	}

	if (IS_PRESSED(KEY::D))
	{
		Vec2 velocity = GetRigidBody()->GetVelocity();

		if (PlayerState::Jump == mState)
		{
			// 반대쪽으로 힘이 작용하고 있을 때 일정량 보정하고 뒤집어준다
			if (velocity.x < 0.f && NotInDash())
				GetRigidBody()->SetVelocity(Vec2(-velocity.x / 1.5f, velocity.y));

			// 현재 X방향 속도가 최대치에 도달하지 않은 경우 값 증가
			if (mJumpXMaxValue > GetRigidBody()->GetVelocity().x)
				GetRigidBody()->AddVelocity(Vec2(5.f, 0.f));
		}
		else
		{
			if (NotInDash())
				GetRigidBody()->SetVelocity(Vec2(PLAYER_SPEED, velocity.y));
		}
	}

	//현재 방향 기록
	mPrevDir = mDir;

	// 마우스 방향에 따라 현재 방향 변경 
	if (MOUSE_POS.x > RENDER_POS(pos).x)
		mDir = PLAYER_DIR::RIGHT;
	else
		mDir = PLAYER_DIR::LEFT;

	
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

	if (nullptr != mDashEffect)
		mDashEffect->Update();
	
}

void Player::StateUpdate()
{
	if (false == GetGround())
	{
		if (nullptr != mState)
			mState->Exit();

		mState = PlayerState::Jump;
	}

	if (PlayerState::Jump != mState)
	{
		if (IS_PRESSED(KEY::A) || IS_PRESSED(KEY::D))
		{
			if (nullptr != mState)
				mState->Exit();

			mState = PlayerState::Walk;
		}

		if (IS_RELEASED(KEY::A) && IS_RELEASED(KEY::D))
		{
			if (nullptr != mState)
				mState->Exit();

			Vec2 velocity = GetRigidBody()->GetVelocity();
			GetRigidBody()->SetVelocity(Vec2(0.f, velocity.y));
			mState = PlayerState::Idle;
		}
	}



	if (IS_RELEASED(KEY::A) && IS_RELEASED(KEY::D))
	{
		Vec2 velocity = GetRigidBody()->GetVelocity();
	/*	GetRigidBody()->SetVelocity(Vec2(0.f, velocity.y));*/
	}

	if (IS_PRESSED(KEY::W) || IS_PRESSED(KEY::SPACE))
	{
		if (nullptr != mState)
			mState->Exit();

		mState = PlayerState::Jump;
		SetGround(false);
	}

	InventoryUI* invenUI =
		static_cast<InventoryUI*>(UIMgr::GetInstance().GetUI(UI_TYPE::INVENTORY));

	if (nullptr != invenUI)
	{
		bool InvenState = invenUI->GetState();
		if (false == InvenState && IS_JUST_PRESSED(KEY::V))
		{
			EventRegisteror::GetInstance().EnableUI(UI_TYPE::INVENTORY);
		}

		else if (true == InvenState && (IS_JUST_PRESSED(KEY::V) || IS_JUST_PRESSED(KEY::ESC)))
		{
			EventRegisteror::GetInstance().DisableUI(UI_TYPE::INVENTORY);
		}
	}

	

	if (false == GetGround())
		SetGravity(true);
	else
		SetGravity(false);
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
	EquipItemRender();
	GameObject::Render();
	if (nullptr != mEffect)
		mEffect->Render();

	if (nullptr != mDashEffect)
		mDashEffect->Render();


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
		SetGround(true);
		SetGravity(false);
		mFall = false;
		mDecDash = false;
		mAccDash = false;
		Vec2 velocity = GetRigidBody()->GetVelocity();
		GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
		mState = PlayerState::Idle;
		mJumpYValue = 700.f;
		mJumpXValue = 0.f;
	}
}

void Player::OnCollisionExit(Collider* _other)
{
	if (_other->GetOwner()->GetType() == OBJECT_TYPE::WALL)
	{
		SetGround(false);
		SetGravity(true);
	}
}


void Player::EquipItemUpdate()
{
	for (int i = 0; i < (UINT)ITEM_TYPE::END; ++i)
	{
		if (nullptr != mEquipItems[i])
			mEquipItems[i]->Update();
	}
}

void Player::EquipItemRender()
{
	for (int i = 0; i < (UINT)ITEM_TYPE::END; ++i)
	{
		if (nullptr != mEquipItems[i])
			mEquipItems[i]->Render();
	}
}

void Player::SetEquipItem(Item* _item)
{
	ITEM_TYPE itemType = _item->GetItemType();
	mEquipItems[(UINT)itemType] = _item;
}

