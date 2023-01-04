#include "pch.h"
#include "BossMonster.h"
#include "Collider.h"
#include "AI.h"
#include "FontMgr.h"
#include "PlayerEffect.h"
#include "Player.h"
#include "Bullet.h"
#include "CameraMgr.h"
#include "Sound.h"
#include "ResourceMgr.h"

BossMonster::BossMonster()
	:mSound(nullptr)
{
	mSound = LOAD_SOUND(L"BelialLastHit", L"Sound\\BelialLastHit.wav");
	mHitSound = LOAD_SOUND(L"MonsterHit", L"Sound\\MonsterHit.wav");
}

BossMonster::~BossMonster()
{
}

void BossMonster::Initialize()
{
	Monster::Initialize();
}

void BossMonster::Update()
{
	Monster::Update();
}

void BossMonster::Render()
{
	if (nullptr != mAI)
		mAI->Render();

	GameObject::Render();
}

void BossMonster::Destroy()
{
	Monster::Destroy();
}

void BossMonster::OnCollision(Collider* _other)
{
}

void BossMonster::OnCollisionEnter(Collider* _other)
{
	// 플레이어의 공격에 피격되는 처리


	if (OBJECT_TYPE::PLAYER_EFFECT == _other->GetOwner()->GetType())
	{
		if (nullptr != mHitSound)
		{
			mHitSound->Play(false);
		}

		SetHit();
		PlayerEffect* playerEffect = static_cast<PlayerEffect*>(_other->GetOwner());
		Player* player = Player::GetPlayer();
		float minAtt = playerEffect->GetMinAtt();
		float maxAtt = playerEffect->GetMaxAtt();

		float playerAtt = player->GetPlayerInfo().mAtt;

		Vec2 pos = GetPos();
		Vec2 playerPos = player->GetPos();
		Vec2 dir = pos - playerPos;

		float curHP = GetCurHP();

		int att = (int)(minAtt + (rand() % (int)(maxAtt - minAtt)));

		float damage = (att + playerAtt);
		curHP -= damage;
		pos.y -= 80;

		int rand_x = rand() % 10;
		int rand_y = rand() % 10;
		int sign = rand() % 2;

		if (false == sign)
		{
			rand_x *= -1;
			rand_y *= -1;
		}

		pos.x += rand_x;
		pos.y += rand_y;

		FontMgr::GetInstance().OutputDamage((int)damage, pos);
		SetCurHP(curHP);

		CameraMgr::GetInstance().RemoveEffect();
		CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::BOSS_SHAKE, 0.1f);
	}

	if (OBJECT_TYPE::MISSILE_FROM_PLAYER == _other->GetOwner()->GetType())
	{
		if (nullptr != mHitSound)
		{
			mHitSound->Play(false);
		}

		SetHit();
		Bullet* bullet = static_cast<Bullet*>(_other->GetOwner());
		BulletInfo info = bullet->GetBulletInfo();

		Player* player = Player::GetPlayer();
		float playerAtt = player->GetPlayerInfo().mAtt;

		float curHP = GetCurHP();

		float minAtt = info.mMinAtt;
		float maxAtt = info.mMaxAtt;

		float damage = minAtt + rand() % (int)(maxAtt - minAtt);
		curHP -= damage;

		Vec2 pos = GetPos();
		pos.y -= 80;

		int rand_x = rand() % 10;
		int rand_y = rand() % 10;
		int sign = rand() % 2;

		if (false == sign)
		{
			rand_x *= -1;
			rand_y *= -1;
		}

		pos.x += rand_x;
		pos.y += rand_y;

		FontMgr::GetInstance().OutputDamage((int)damage, pos);
		SetCurHP(curHP);

		CameraMgr::GetInstance().RemoveEffect();
		CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::BOSS_SHAKE, 0.1f);
	}

	if (0.f > GetCurHP())
	{
		Killed();

		if (nullptr != mSound)
		{
			mSound->Play(false);
		}
	}

}

void BossMonster::OnCollisionExit(Collider* _other)
{
}
