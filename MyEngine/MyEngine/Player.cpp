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
#include "EatState.h"
#include "GameObject.h"
#include "Effect.h"
#include "RigidBody.h"
#include "InventoryUI.h"
#include "UIMgr.h"
#include "EventRegisteror.h"
#include "ShortSword.h"
#include "DashEffect.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Tile.h"

Player* Player::mPlayer = nullptr;
IdleState* PlayerState::Idle = nullptr;
WalkState* PlayerState::Walk = nullptr;
JumpState* PlayerState::Jump = nullptr;
EatState*  PlayerState::Eat = nullptr;

Player::Player()
	:mJumpYValue(700.f)
	,mJumpYMinValue(0.f)
	,mJumpXValue(0.f)
	,mJumpXMaxValue(300.f)
	,mFall(false)
	,mDashAccTime(0.f)
	,mImgCount(0)
	,mDashAccMaxTime(.1f)
	,mDecTime(0.f)
	,mDecMaxTime(.08f)
	,mDecDash(false)
	,mAccDash(false)
	,mImgDuration(0.007f)
	,mCurImgDuration(0.007f)
	,mStop(false)
	,mGroundFlag(false)
{
	SetType(OBJECT_TYPE::PLAYER);
	SetSize(Vec2(96.f, 96.f));

#pragma region PLAYER_STATE_INITIALIZE
	mPlayer = this;
	PlayerState::Idle = new IdleState(this);
	PlayerState::Walk = new WalkState(this);
	PlayerState::Jump = new JumpState(this);
	PlayerState::Eat = new EatState(this);
	mState = PlayerState::Idle;
#pragma endregion

#pragma region PLAYER_TEXTURE_INITIALIZE
	mDefaultTexture = ResourceMgr::GetInstance().Load<Texture>(L"PLAYER_ANIMATION", L"Texture\\player_animation.bmp");
	mDashTexture = ResourceMgr::GetInstance().Load<Texture>(L"PLAYER_DASH_EFFECT", L"Texture\\player_dash_effect.bmp");
	Texture* dust = ResourceMgr::GetInstance().Load<Texture>(L"PLAYER_DUST", L"Texture\\player_dust.bmp");
	Texture* noneAnim = ResourceMgr::GetInstance().Load<Texture>(L"PLAYER_NONE_ANIM", L"Texture\\NoneAnim.bmp");
#pragma endregion

#pragma region PLAYER_COMPONENT_INITIALIZE
	CreateComponent(new Collider);
	GetCollider()->SetOwner(this);

	GetCollider()->SetSize(Vec2(30.f, 30.f));
	GetCollider()->SetOffset(Vec2(0.f, -15.f));

	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	CreateComponent(new RigidBody);
	GetRigidBody()->SetOwner(this);
#pragma endregion

#pragma region PLAYER_DUST_EFFECT_INITIALIZE
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
#pragma endregion

#pragma region PLAYER_DASH_EFFECT_INITIALIZE
	for (int i = 0; i < AFTER_IMAGE_TOTAL; ++i)
	{
		mDashEffect[i] = new DashEffect;
		mDashEffect[i]->SetOwner(this);
		mDashEffect[i]->SetSize(GetSize());
		mDashEffect[i]->SetOffset(Vec2(0.f, 0.f));
		mDashEffect[i]->SetTexture(mDashTexture);
	}
#pragma endregion
	
#pragma region PLAYER_ANIMATION
	GetAnimator()->RegisterAnimation(L"PLAYER_IDLE_LEFT", mDefaultTexture, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 5);
	GetAnimator()->RegisterAnimation(L"PLAYER_IDLE_RIGHT", mDefaultTexture, Vec2(0.f, 32.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 5);
	GetAnimator()->RegisterAnimation(L"PLAYER_WALK_LEFT", mDefaultTexture, Vec2(0.f, 64.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.05f, 8);
	GetAnimator()->RegisterAnimation(L"PLAYER_WALK_RIGHT", mDefaultTexture, Vec2(0.f, 96.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.05f, 8);
	GetAnimator()->RegisterAnimation(L"PLAYER_JUMP_LEFT", mDefaultTexture, Vec2(0.f, 128.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.2f, 1);
	GetAnimator()->RegisterAnimation(L"PLAYER_JUMP_RIGHT", mDefaultTexture, Vec2(0.f, 160.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.2f, 1);
	GetAnimator()->RegisterAnimation(L"PLAYER_NONE_ANIM", noneAnim, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.2f, 1);
#pragma endregion

#pragma region PLAYER_EQUIP_ITEM_INITIALIZE
	for (int i = 0; i < (UINT)EQUIP_TYPE::END; ++i)
	{
		mEquipItems[i] = nullptr;
	}

	ShortSword* shortSword = new ShortSword;
	shortSword->Initialize();
	SetEquipItem(shortSword);
#pragma endregion

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

	if (nullptr != PlayerState::Eat)
		delete PlayerState::Eat;

	if (nullptr != mEffect)
		delete mEffect;

	for (int i = 0; i < AFTER_IMAGE_TOTAL; ++i)
	{
		if (nullptr != mDashEffect[i])
			delete mDashEffect[i];
	}
	
	for (int i = 0; i < (UINT)EQUIP_TYPE::END; ++i)
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
	GetAnimator()->SelectAnimation(L"PLAYER_IDLE_RIGHT");
}

void Player::Update()
{

	if (!mStop)
		mPrevPos = GetPos();

	GameObject::Update();

	if (GetRigidBody()->GetVelocity_Y() > 800.f)
		GetRigidBody()->SetVelocity_Y(800.f);
	
	EquipItemUpdate();

	if (mStop)
		return;
	
	MoveUpdate();
	EffectUpdate();
	StateUpdate();
	AnimationUpdate();

	wchar_t szBuffer[256] = {};
	swprintf_s(szBuffer, L"groundType : %d", mGroundType);
	SetWindowText(APP_INSTANCE.GetHwnd(), szBuffer);

	if (IS_PRESSED(KEY::G))
	{
		if (GetGravity())
			SetGravity(false);
		else
			SetGravity(true);
	}
	
	mPrevState = mState;
}

void Player::MoveUpdate()
{
	// 감속 시간이 0이상이고 감속 최대치보다 작은 경우
	if (mDecDash && mDecTime < mDecMaxTime)
		DashDeceleration();
	

	// 가속 플래그가 켜져있고, 가속 시간이 최대 가속시간을 넘었다면
	DashAcceleration();
	
	Vec2 pos = GetPos();


	if (IS_PRESSED(KEY::W) || IS_PRESSED(KEY::SPACE))
	{
		if (IS_PRESSED(KEY::S))
		{
			//TODO
		}

		else
		{
			// value 값을 주고 누르고있으면 떨어지는 구조, 바닥에 착지하면 초기화

			Vec2 velocity = GetRigidBody()->GetVelocity();

			if (mJumpYValue > mJumpYMinValue)
			{
				if (!mFall)
				{
					GetRigidBody()->SetVelocity(Vec2(velocity.x, -mJumpYValue));
					mJumpYValue -= DT * 1300.f;
				}
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

		// 지금 상태가 Ground인데, 대쉬 방향이 하단 좌우 몇도 이하면 해제안함

		mousePos.Norm();
		float angle = acos(dashDir.Dot(mousePos));
		angle = Math::RadianToDegree(angle);

		if (angle <= 15.f && angle >= 75.f)
		{
			SetGround(false);
			mFall = true;
		}

		mAccDash = true;
		mDashAccTime = 0.f;
		mImgCount = 0;
		mDashSpeed = Vec2(dashDir * PLAYER_DASH_SPEED);

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
			Vec2 destVelocity = Vec2(velocity.x - 5000.f * DT, velocity.y);
			Vec2 curVelocity = Math::Lerp(velocity, destVelocity, 0.2f);

			if (velocity.x < -mJumpXMaxValue)
				return;

			if (velocity.x > 0.f && NotInDash())
				GetRigidBody()->SetVelocity(Vec2(-(velocity.x / 2.f), velocity.y));
			else
				GetRigidBody()->SetVelocity(curVelocity);

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
			Vec2 destVelocity = Vec2(velocity.x + 5000.f * DT, velocity.y);
			Vec2 curVelocity = Math::Lerp(velocity, destVelocity, 0.2f);

			//// 반대쪽으로 힘이 작용하고 있을 때 일정량 보정하고 뒤집어준다

			if (velocity.x > mJumpXMaxValue)
				return;

			if (velocity.x < 0.f && NotInDash())
				GetRigidBody()->SetVelocity(Vec2(-(velocity.x / 2.f), velocity.y));

			else 
				GetRigidBody()->SetVelocity(curVelocity);

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

	for (int i = 0; i < AFTER_IMAGE_TOTAL; ++i)
	{
		if (nullptr != mDashEffect[i])
			mDashEffect[i]->Update();
	}
	
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

			if (!mAccDash)
			{
				GetRigidBody()->SetVelocity_X_Zero();
				mState = PlayerState::Idle;
			}
		}
	}

	InventoryUI* invenUI = GET_UI(UI_TYPE::INVENTORY);

	if (nullptr != invenUI)
	{
		bool InvenState = invenUI->GetState();
		if (false == InvenState 
			&& IS_JUST_PRESSED(KEY::V))
		{
			EventRegisteror::GetInstance().EnableUI(UI_TYPE::INVENTORY);
		}

		else if (true == InvenState 
			&& (IS_JUST_PRESSED(KEY::V) 
			||  IS_JUST_PRESSED(KEY::ESC)))
		{
			EventRegisteror::GetInstance().DisableUI(UI_TYPE::INVENTORY);
		}
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
	if (mStop)
		return;

	EquipItemRender();
	GameObject::Render();

	if (nullptr != mEffect)
		mEffect->Render();

	for (int i = 0; i < AFTER_IMAGE_TOTAL; ++i)
	{
		if (nullptr != mDashEffect[i])
			mDashEffect[i]->Render();
	}

	// Debug Info
	wchar_t isGround[256] = {};
	wchar_t isGravity[256] = {};
	swprintf_s(isGround, L"Ground : %s", (GetGround() ? L"O" : L"X"));
	swprintf_s(isGravity, L"Gravity : %s", (GetGravity() ? L"O" : L"X"));
	TextOut(BACK_BUF_DC, 10, 10, isGround, (int)wcslen(isGround));
	TextOut(BACK_BUF_DC, 10, 30, isGravity, (int)wcslen(isGravity));

	wchar_t velocity[256] = {};
	swprintf_s(velocity, L"velocity_x : %f, velocity_y : %f", GetRigidBody()->GetVelocity_X(), GetRigidBody()->GetVelocity_Y());
	TextOut(BACK_BUF_DC, 10, 50, velocity, (int)wcslen(velocity));
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
	if (_other->GetOwner()->GetType() == OBJECT_TYPE::WALL)
	{
		if (0 == GetCollider()->GetColCnt())
			OutGround();
	}

	if (_other->GetOwner()->GetType() == OBJECT_TYPE::FOOTHOLD)
	{
		if (0 == GetCollider()->GetColCnt())
			OutGround();
	}
}


void Player::EquipItemUpdate()
{
	InventoryUI* inven = GET_UI(UI_TYPE::INVENTORY);
	INVENTORY_SLOT curSlot = inven->GetSlot();

	for (int i = 0; i < (UINT)EQUIP_TYPE::END; ++i)
	{

		if (nullptr != mEquipItems[i])
		{
			if (INVENTORY_SLOT::LEFT_SLOT == curSlot)
			{
				if ((UINT)EQUIP_TYPE::WEAPON_2 == i)
					continue;

				if ((UINT)EQUIP_TYPE::SHIELD_2 == i)
					continue;
			}

			else if (INVENTORY_SLOT::RIGHT_SLOT == curSlot)
			{
				if ((UINT)EQUIP_TYPE::WEAPON_1 == i)
					continue;

				if ((UINT)EQUIP_TYPE::SHIELD_1 == i)
					continue;
			}

			mEquipItems[i]->Update();
		}
	}
}

void Player::EquipItemRender()
{
	InventoryUI* inven = GET_UI(UI_TYPE::INVENTORY);
	INVENTORY_SLOT curSlot = inven->GetSlot();

	for (int i = 0; i < (UINT)EQUIP_TYPE::END; ++i)
	{
		if (nullptr != mEquipItems[i])
		{
			if (INVENTORY_SLOT::LEFT_SLOT == curSlot)
			{
				if ((UINT)EQUIP_TYPE::WEAPON_2 == i)
					continue;

				if ((UINT)EQUIP_TYPE::SHIELD_2 == i)
					continue;
			}

			else if (INVENTORY_SLOT::RIGHT_SLOT == curSlot)
			{
				if ((UINT)EQUIP_TYPE::WEAPON_1 == i)
					continue;

				if ((UINT)EQUIP_TYPE::SHIELD_1 == i)
					continue;
			}

			mEquipItems[i]->Render();
		}
	}
}

void Player::DashEffectReset()
{
	mDashEffect[mImgCount]->SetPos(GetPos());
	mDashEffect[mImgCount]->Reset();
}

void Player::DashDeceleration()
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

void Player::DashAcceleration()
{
	if (mAccDash && mDashAccTime >= mDashAccMaxTime)
	{
		// 가속을 해제하고 감속을 시작한다.
		mAccDash = false;
		mDecDash = true;
		mDecTime = DT;
		mDashSpeed = GetRigidBody()->GetVelocity();
	}

	// 가속중일 때
	else
	{
		// 이미지 카운트가 최대치 미만이면
		if (mImgCount < AFTER_IMAGE_TOTAL)
		{
			if (mImgDuration > mCurImgDuration)
			{
				mCurImgDuration += DT;
			}
			else
			{
				DashEffectReset();
				++mImgCount;
				mCurImgDuration = 0.f;
			}
		}

		mDashAccTime += DT;
	}
}

void Player::InGround()
{
	SetGround(true);
	mFall = false;
	mDecDash = false;
	mAccDash = false;
	GetRigidBody()->SetVelocity_Y_Zero();
	mState = PlayerState::Idle;
	mJumpYValue = 700.f;
	mJumpXValue = 0.f;
}

void Player::OutGround()
{
	SetGround(false);
}

inline void Player::SetStop(bool _flag)
{
	mStop = _flag;
	GetRigidBody()->SetVelocity(ZERO_VECTOR);
}

void Player::SetEquipItem(Item* _item)
{
	ITEM_TYPE itemType = _item->GetItemType();
	InventoryUI* inven = GET_UI(UI_TYPE::INVENTORY);

	switch (itemType)
	{
	case ITEM_TYPE::WEAPON:
	{
		INVENTORY_SLOT curSlot = inven->GetSlot();
		switch (curSlot)
		{
		case INVENTORY_SLOT::LEFT_SLOT:
			mEquipItems[(UINT)EQUIP_TYPE::WEAPON_1] = _item;
			break;
		case INVENTORY_SLOT::RIGHT_SLOT:
			mEquipItems[(UINT)EQUIP_TYPE::WEAPON_2] = _item;
			break;
		}
	}

		break;
	case ITEM_TYPE::SECONDARY:
		break;
	case ITEM_TYPE::ACCESSORIES:
		break;
	}
	mEquipItems[(UINT)itemType] = _item;
}

