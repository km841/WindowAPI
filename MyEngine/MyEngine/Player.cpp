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
#include "Foothold.h"

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
	,mHit(false)
	, mInvinMaxTime(0.5f)
	, mInvinTime(0.f)
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

	GetCollider()->SetSize(Vec2(30.f, 20.f));
	GetCollider()->SetOffset(Vec2(0.f, -10.f));

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

	Animation* dustLeft = GetAnimator()->CreateAnimation(L"PLAYER_DUST_LEFT", dust, Vec2(0.f, 0.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 0.05f, 6);
	Animation* dustRight = GetAnimator()->CreateAnimation(L"PLAYER_DUST_RIGHT", dust, Vec2(0.f, 48.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 0.05f, 6);

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
	
#pragma region PLAYER_ANIMATION_REGISTER
	GetAnimator()->RegisterAnimation(L"PLAYER_IDLE_LEFT", mDefaultTexture, Vec2(0.f, 0.f), Vec2(96.f, 96.f), Vec2(96.f, 0.f), 0.1f, 5);
	GetAnimator()->RegisterAnimation(L"PLAYER_IDLE_RIGHT", mDefaultTexture, Vec2(0.f, 96.f), Vec2(96.f, 96.f), Vec2(96.f, 0.f), 0.1f, 5);
	GetAnimator()->RegisterAnimation(L"PLAYER_WALK_LEFT", mDefaultTexture, Vec2(0.f, 192.f), Vec2(96.f, 96.f), Vec2(96.f, 0.f), 0.05f, 8);
	GetAnimator()->RegisterAnimation(L"PLAYER_WALK_RIGHT", mDefaultTexture, Vec2(0.f, 288.f), Vec2(96.f, 96.f), Vec2(96.f, 0.f), 0.05f, 8);
	GetAnimator()->RegisterAnimation(L"PLAYER_JUMP_LEFT", mDefaultTexture, Vec2(0.f, 384.f), Vec2(96.f, 96.f), Vec2(96.f, 0.f), 0.2f, 1);
	GetAnimator()->RegisterAnimation(L"PLAYER_JUMP_RIGHT", mDefaultTexture, Vec2(0.f, 480.f), Vec2(96.f, 96.f), Vec2(96.f, 0.f), 0.2f, 1);
	GetAnimator()->RegisterAnimation(L"PLAYER_NONE_ANIM", noneAnim, Vec2(0.f, 0.f), Vec2(96.f, 96.f), Vec2(96.f, 0.f), 0.2f, 1);
#pragma endregion

#pragma region PLAYER_EQUIP_ITEM_REGISTER
	for (int i = 0; i < (UINT)EQUIP_TYPE::END; ++i)
	{
		mEquipItems[i] = nullptr;
	}
	ShortSword* shortSword = new ShortSword;
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
	{
		delete mEffect;
		mEffect = nullptr;
	}

	for (int i = 0; i < AFTER_IMAGE_TOTAL; ++i)
	{
		if (nullptr != mDashEffect[i])
		{
			delete mDashEffect[i];
			mDashEffect[i] = nullptr;
		}
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

	for (int i = 0; i < (UINT)EQUIP_TYPE::END; ++i)
	{
		if (nullptr != mEquipItems[i])
			mEquipItems[i]->Initialize();
	}

}

void Player::Update()
{

	if (!mStop)
		mPrevPos = GetPos();

	GameObject::Update();

	if (GetRigidBody()->GetVelocity_Y() > 800.f)
		GetRigidBody()->SetVelocity_Y(800.f);

	if (mHit && (mInvinTime > mInvinMaxTime))
	{
		mHit = false;
		mInvinTime = 0.f;
	}

	else
	{
		if (mHit)
		{
			mInvinTime += DT;
		}
		
	}
	
	EquipItemUpdate();

	if (mStop)
		return;
	
	MoveUpdate();
	GroundStateUpdate();
	EffectUpdate();
	StateUpdate();
	AnimationUpdate();
	
	mPrevState = mState;
}

void Player::MoveUpdate()
{
	// ���� �ð��� 0�̻��̰� ���� �ִ�ġ���� ���� ���
	if (mDecDash && mDecTime < mDecMaxTime)
		DashDeceleration();
	

	// ���� �÷��װ� �����ְ�, ���� �ð��� �ִ� ���ӽð��� �Ѿ��ٸ�
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
			// value ���� �ְ� ������������ �������� ����, �ٴڿ� �����ϸ� �ʱ�ȭ

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

		// ���� ���°� Ground�ε�, �뽬 ������ �ϴ� �¿� � ���ϸ� ��������

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
			Vec2 destVelocity = Vec2(velocity.x - 300.f, velocity.y);
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
			{
				if (COLLISION_TYPE::LINE == GetCollisionType())
				{

					Vec2 dirVec = GetDirectionVector();
					if (0.f != dirVec.x || 0.f != dirVec.y)
					{
						dirVec *= -PLAYER_SPEED;
						GetRigidBody()->SetVelocity(dirVec);
					}

				}

				else
				{
					GetRigidBody()->SetVelocity_X(-PLAYER_SPEED);
				}
			}
		}
	}

	if (IS_PRESSED(KEY::D))
	{
		Vec2 velocity = GetRigidBody()->GetVelocity();

		if (PlayerState::Jump == mState)
		{
			Vec2 destVelocity = Vec2(velocity.x + 300.f, velocity.y);
			Vec2 curVelocity = Math::Lerp(velocity, destVelocity, 0.2f);

			// �ݴ������� ���� �ۿ��ϰ� ���� �� ������ �����ϰ� �������ش�

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
			{
				if (COLLISION_TYPE::LINE == GetCollisionType())
				{

					Vec2 dirVec = GetDirectionVector();
					if (0.f != dirVec.x || 0.f != dirVec.y)
					{
						dirVec *= PLAYER_SPEED;
						GetRigidBody()->SetVelocity(dirVec);
					}

				}

				else
				{
					GetRigidBody()->SetVelocity_X(PLAYER_SPEED);
				}
			}

		}
	}

	//���� ���� ���
	mPrevDir = mDir;

	// ���콺 ���⿡ ���� ���� ���� ���� 
	if (MOUSE_POS.x > RENDER_POS(pos).x)
		mDir = DIR::RIGHT;
	else
		mDir = DIR::LEFT;

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

		if (IS_JUST_RELEASED(KEY::A) || IS_JUST_RELEASED(KEY::D))
		{
			GetRigidBody()->SetVelocity_Zero();
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

void Player::GroundStateUpdate()
{
	const std::vector<Relation>& relations = GetRelations();
	bool isGround = false;
	for (int i = 0; i < relations.size(); ++i)
	{
		if (OBJECT_TYPE::WALL == relations[i].mOther->GetType() ||
			OBJECT_TYPE::FOOTHOLD == relations[i].mOther->GetType())
		{
			isGround = true;
		}
	}

	if (!isGround)
	{
		SetGround(false);
	}
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
	wchar_t isGround[COMMENT_MAX_SIZE] = {};
	wchar_t isGravity[COMMENT_MAX_SIZE] = {};
	swprintf_s(isGround, L"Ground : %s", (GetGround() ? L"O" : L"X"));
	swprintf_s(isGravity, L"Gravity : %s", (GetGravity() ? L"O" : L"X"));
	TextOut(BACK_BUF_DC, 10, 10, isGround, (int)wcslen(isGround));
	TextOut(BACK_BUF_DC, 10, 30, isGravity, (int)wcslen(isGravity));

	wchar_t velocity[COMMENT_MAX_SIZE] = {};
	swprintf_s(velocity, L"velocity_x : %f, velocity_y : %f", GetRigidBody()->GetVelocity_X(), GetRigidBody()->GetVelocity_Y());
	TextOut(BACK_BUF_DC, 10, 50, velocity, (int)wcslen(velocity));

	Vec2 mouserRenderPos = RENDER_POS(MOUSE_POS);
	wchar_t mousePos[COMMENT_MAX_SIZE] = {};
	swprintf_s(mousePos, L"mouse_x : %f, mouse_y : %f", MOUSE_POS.x, MOUSE_POS.y);
	TextOut(BACK_BUF_DC, 10, 70, mousePos, (int)wcslen(mousePos));

	Vec2 playerRenderPos = RENDER_POS(GetPos());
	wchar_t playerPos[COMMENT_MAX_SIZE] = {};
	swprintf_s(playerPos, L"player_x : %f, player_y : %f", playerRenderPos.x, playerRenderPos.y);
	TextOut(BACK_BUF_DC, 10, 90, playerPos, (int)wcslen(playerPos));

	Vec2 dirVec = GetDirectionVector();
	wchar_t dirVecComment[COMMENT_MAX_SIZE] = {};
	swprintf_s(dirVecComment, L"dirv_x : %f, dirv_y : %f", dirVec.x, dirVec.y);
	TextOut(BACK_BUF_DC, 10, 150, dirVecComment, (int)wcslen(dirVecComment));
}

void Player::Destroy()
{
	for (int i = 0; i < (UINT)EQUIP_TYPE::END; ++i)
	{
		if (nullptr != mEquipItems[i])
			mEquipItems[i]->Destroy();
	}
}

void Player::OnCollision(Collider* _other)
{

}

void Player::OnCollisionEnter(Collider* _other)
{
	if (OBJECT_TYPE::MONSTER_EFFECT == _other->GetOwner()->GetType() || 
		OBJECT_TYPE::MISSILE_FROM_MONSTER == _other->GetOwner()->GetType())
	{
		CameraMgr::GetInstance().RemoveEffect();
		CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::SHAKE, .1f);
		CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::HIT, .3f);
		mHit = true;
	}

}

void Player::OnCollisionExit(Collider* _other)
{

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
	// ���� ���ӽð��� �ִ� ���ӽð����� ������ 1�� �� �ݴ� ���� ���Ѵ�.
	float ratio = 1.f - (mDecTime / mDecMaxTime);
	Vec2 curSpeed = mDashSpeed * ratio;

	GetRigidBody()->SetVelocity(curSpeed);

	mDecTime += DT;
	// �̹� ���������� ���� �ִ� ���ӽð��� �Ǿ��ٸ� ������ �����Ѵ�.
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
		// ������ �����ϰ� ������ �����Ѵ�.
		mAccDash = false;
		mDecDash = true;
		mDecTime = DT;
		mDashSpeed = GetRigidBody()->GetVelocity();
	}

	// �������� ��
	else
	{
		// �̹��� ī��Ʈ�� �ִ�ġ �̸��̸�
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

