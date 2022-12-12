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

Texture* Monster::mHPBaseTex = nullptr;
Texture* Monster::mHPTex     = nullptr;

Monster::Monster()
	: mDead(false)
	, mAI(nullptr)
	, mInfo()
	, mDir(DIR::LEFT)
	, mPrevDir(DIR::END)
	, mMoney(0)
{
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

	// 삭제될 때 씬에서도 지워줘야 함
	
	
	//if (nullptr != mEffect)
	//{
	//	delete mEffect;
	//	mEffect = nullptr;
	//}
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


}

void Monster::Render()
{
	if (nullptr != mAI)
		mAI->Render();

	// 몬스터의 체력이 100%가 아니라면 hpbar 위치를 받아서 출력


	GameObject::Render();
	float ratio = mInfo.mCurHP / mInfo.mMaxHP;
	if (1.0f > ratio && false == mDead)
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

	// 씬의 Exit에서 삭제하도록 함
	//EventRegisteror::GetInstance().DeleteObject(mEffect);
	//mEffect = nullptr;
}

void Monster::OnCollision(Collider* _other)
{
}

void Monster::OnCollisionEnter(Collider* _other)
{
	if (OBJECT_TYPE::PLAYER_EFFECT == _other->GetOwner()->GetType())
	{
		// 무기에서 이펙트에 공격력을 전달?
		PlayerEffect* playerEffect = static_cast<PlayerEffect*>(_other->GetOwner());
		Player* player = Player::GetPlayer();
		float att = playerEffect->GetAtt();
		float playerAtt = player->GetPlayerInfo().mAtt;

		Vec2 pos = GetPos();
		Vec2 playerPos = player->GetPos();
		Vec2 dir = pos - playerPos;

		//dir.Norm();
		//dir.x *= 3;

		//SetPos(pos + dir);

		float curHP = GetCurHP();

		float damage = (att + playerAtt);
		curHP -= damage;
		pos.y -= 80;
		FontMgr::GetInstance().OutputDamage((int)damage, pos);
		SetCurHP(curHP);
		if (curHP > 0.f)
		{
			if (MONSTER_STATE::ATTACK != mAI->GetCurState()->GetMonsterState())
				EventRegisteror::GetInstance().ChangeMonsterState(mAI, MONSTER_STATE::ATTACK);
		}
		else
		{
			if (!mDead)
			{
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

				GetEffect()->Destroy();
				mDead = true;
				EventRegisteror::GetInstance().ChangeMonsterState(mAI, MONSTER_STATE::DEAD);
			}
		}
	}

	if (OBJECT_TYPE::MISSILE_FROM_PLAYER == _other->GetOwner()->GetType())
	{
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
				mAI->ChangeState(MONSTER_STATE::TRACE);
			}
		}
		else
		{
			if (!mDead)
			{
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

				GetEffect()->Destroy();
				mDead = true;
				EventRegisteror::GetInstance().ChangeMonsterState(mAI, MONSTER_STATE::DEAD);
			}

		}
	}
}

void Monster::OnCollisionExit(Collider* _other)
{

}
