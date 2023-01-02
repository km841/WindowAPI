#include "pch.h"
#include "Monster.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "EventRegisteror.h"
#include "CameraMgr.h"
#include "RigidBody.h"
#include "AI.h"
#include "MonsterEffect.h"
#include "Animation.h"
#include "PlayerEffect.h"
#include "MonsterEffect.h"
#include "Player.h"
#include "MonsterState.h"
#include "Bullet.h"
#include "FontMgr.h"
#include "Gold.h"
#include "Coin.h"
#include "GoldBar.h"
#include "Sound.h"

Texture* Monster::mHPBaseTex = nullptr;
Texture* Monster::mHPTex     = nullptr;

Monster::Monster()
	: mAI(nullptr)
	, mInfo()
	, mDir(DIR::LEFT)
	, mPrevDir(DIR::END)
	, mMoney(0)
	, mAttFixFrame(0)
	, mHitMaxTime(0.05f)
	, mHitCurTime(0.f)
	, mSound(nullptr)
	, mDieSound(nullptr)
{
	mSound = LOAD_SOUND(L"MonsterHit", L"Sound\\MonsterHit.wav");
	mDieSound = LOAD_SOUND(L"MonsterDie", L"Sound\\MonsterDie.wav");
	SetType(OBJECT_TYPE::MONSTER);

	CreateComponent(new Collider);
	GetCollider()->SetOwner(this);

	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	CreateComponent(new RigidBody);
	GetRigidBody()->SetOwner(this);

	Texture* monsterDeadTex = ResourceMgr::GetInstance().Load<Texture>(L"MonsterDeadTex", L"Texture\\MonsterDeadTex.bmp");

	Animation* deadAnim = GetAnimator()->CreateAnimation(
		L"MonsterDeadAnim",
		monsterDeadTex,
		Vec2(0.f, 0.f),
		Vec2(192.f, 192.f),
		Vec2(192.f, 0.f),
		0.05f,
		11
	);

	mMoney = 1 + (rand() % 149);


	deadAnim->SetOffset(Vec2(0.f, 50.f));
	
	GetAnimator()->AddAnimation(L"MonsterDeadAnim", deadAnim);

	if (nullptr == mHPBaseTex)
	{
		mHPBaseTex = ResourceMgr::GetInstance().Load<Texture>(L"MonsterHPBaseTex", L"Texture\\MONSTER_HP_BASE.bmp");
	}

	if (nullptr == mHPTex)
	{
		mHPTex = ResourceMgr::GetInstance().Load<Texture>(L"MonsterHPTex", L"Texture\\MONSTER_HP.bmp");
	}

	
}

Monster::~Monster()
{
	if (nullptr != mAI)
	{
		delete mAI;
		mAI = nullptr;
	}
}

void Monster::Initialize()
{
	mInfo.mCurHP = mInfo.mMaxHP;

	Effect* effect = GetEffect();
	if (nullptr != effect)
	{
		effect->SetPos(GetPos());
		effect->Initialize();
		EventRegisteror::GetInstance().CreateObject(effect, effect->GetType());
	}
	
}

void Monster::Update()
{
	if (nullptr != mAI)
		mAI->Update();

	GameObject::Update();
	HitUpdate();

}

void Monster::Render()
{
	if (nullptr != mAI)
		mAI->Render();

	// ������ ü���� 100%�� �ƴ϶�� hpbar ��ġ�� �޾Ƽ� ���


	GameObject::Render();
	float ratio = mInfo.mCurHP / mInfo.mMaxHP;
	if (1.0f > ratio && false == IsDead())
	{
		Vec2 pos = GetPos();
		pos += mHPBarOffset;
		pos = RENDER_POS(pos);
		Vec2 hpBaseSize = mHPBaseTex->GetSize();
		Vec2 hpSize = mHPTex->GetSize();

		BitBlt(
			BACK_BUF_DC,
			(int)(pos.x - hpBaseSize.x / 2),
			(int)(pos.y - hpBaseSize.y / 2),
			(int)hpBaseSize.x,
			(int)hpBaseSize.y,
			mHPBaseTex->GetDC(),
			0, 0,
			SRCCOPY
		);

		BitBlt(
			BACK_BUF_DC,
			(int)(pos.x - hpSize.x / 2),
			(int)(pos.y - hpSize.y / 2),
			(int)(hpSize.x * ratio),
			(int)hpSize.y,
			mHPTex->GetDC(),
			0, 0,
			SRCCOPY
		);
	}
}

void Monster::Destroy()
{
	if (nullptr != mEffect)
		EventRegisteror::GetInstance().DeleteObject(mEffect);
}

void Monster::HitUpdate()
{
	if (mHit)
	{
		if (mHitMaxTime < mHitCurTime)
		{
			mHit = false;
		}

		else
		{
			mHitCurTime += DT;
		}
	}
}

void Monster::SetHit()
{
	mHit = true;
	mHitCurTime = 0.f;
}

void Monster::OnCollision(Collider* _other)
{
}

void Monster::OnCollisionEnter(Collider* _other)
{
	if (OBJECT_TYPE::PLAYER_EFFECT == _other->GetOwner()->GetType())
	{
		if (nullptr != mSound)
		{
			mSound->Play(false);
		}

		SetHit();
		// ���⿡�� ����Ʈ�� ���ݷ��� ����?
		PlayerEffect* playerEffect = static_cast<PlayerEffect*>(_other->GetOwner());
		Player* player = Player::GetPlayer();
		float att = playerEffect->GetAtt();
		float playerAtt = player->GetPlayerInfo().mAtt;

		Vec2 pos = GetPos();
		Vec2 playerPos = player->GetPos();
		Vec2 dir = pos - playerPos;

		float curHP = GetCurHP();

		float damage = (att + playerAtt);
		curHP -= damage;
		pos.y -= 80;
		FontMgr::GetInstance().OutputDamage((int)damage, pos);
		SetCurHP(curHP);
		if (curHP > 0.f)
		{
			MONSTER_STATE state = mAI->GetCurState()->GetMonsterState();
			if (MONSTER_STATE::IDLE == state ||
				MONSTER_STATE::PATROL == state)
			{

				if (nullptr != mAI->FindState(MONSTER_STATE::TRACE))
					mAI->ChangeState(MONSTER_STATE::TRACE);
				else
					mAI->ChangeState(MONSTER_STATE::ATTACK);
			}
		}
		else
		{
			if (IsAlive())
			{
				if (nullptr != mDieSound)
				{
					mDieSound->Play(false);
				}

				int billion = mMoney / 100;
				int changes = mMoney % 100;
				int coin = changes / 10;

				for (int i = 0; i < billion; ++i)
				{
					int randomAngle = 250 + (rand() % 40);
					Gold::Drop(new GoldBar, GetPos(), 100, (float)randomAngle);
				}

				for (int i = 0; i < coin; ++i)
				{
					int randomAngle = 250 + (rand() % 40);
					Gold::Drop(new Coin, GetPos(), 10, (float)randomAngle);
				}

				MonsterEffect* effect = GetEffect();
				if (nullptr != effect)
				{
					effect->Destroy();
				}
				SetObjState(OBJECT_STATE::DEAD_ANIM);
				EventRegisteror::GetInstance().ChangeMonsterState(mAI, MONSTER_STATE::DEAD);
			}
		}
	}

	if (OBJECT_TYPE::MISSILE_FROM_PLAYER == _other->GetOwner()->GetType())
	{
		if (nullptr != mSound)
		{
			mSound->Play(false);
		}

		SetHit();
		Bullet* bullet = static_cast<Bullet*>(_other->GetOwner());
		BulletInfo info = bullet->GetBulletInfo();

		Player* player = Player::GetPlayer();
		float playerAtt = player->GetPlayerInfo().mAtt;
		
		float curHP = GetCurHP();
		float damage = (info.mAtt + playerAtt);
		curHP -= damage;

		Vec2 pos = GetPos();
		pos.y -= 80;

		FontMgr::GetInstance().OutputDamage((int)damage, pos);
		SetCurHP(curHP);
		if (curHP > 0.f)
		{
			MONSTER_STATE state = mAI->GetCurState()->GetMonsterState();
			if (MONSTER_STATE::IDLE == state || 
				MONSTER_STATE::PATROL == state)
			{
				if (nullptr != mAI->FindState(MONSTER_STATE::TRACE))
					mAI->ChangeState(MONSTER_STATE::TRACE);
				else
					mAI->ChangeState(MONSTER_STATE::ATTACK);
			}
		}
		else
		{
			if (IsAlive())
			{

				if (nullptr != mDieSound)
				{
					mDieSound->Play(false);
				}
				int billion = mMoney / 100;
				int changes = mMoney % 100;
				int coin = changes / 10;

				for (int i = 0; i < billion; ++i)
				{
					int randomAngle = 250 + (rand() % 40);
					Gold::Drop(new GoldBar, GetPos(), 100, (float)randomAngle);
				}

				for (int i = 0; i < coin; ++i)
				{
					int randomAngle = 250 + (rand() % 40);
					Gold::Drop(new Coin, GetPos(), 10, (float)randomAngle);
				}

				MonsterEffect* effect = GetEffect();
				if (nullptr != effect)
				{
					effect->Destroy();
				}
				SetObjState(OBJECT_STATE::DEAD_ANIM);
				EventRegisteror::GetInstance().ChangeMonsterState(mAI, MONSTER_STATE::DEAD);
			}

		}
	}
}

void Monster::OnCollisionExit(Collider* _other)
{

}
