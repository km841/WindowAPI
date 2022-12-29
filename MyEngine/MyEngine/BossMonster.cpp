#include "pch.h"
#include "BossMonster.h"
#include "Collider.h"
#include "AI.h"
#include "FontMgr.h"
#include "PlayerEffect.h"
#include "Player.h"
#include "Bullet.h"

BossMonster::BossMonster()
{
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
	}

}

void BossMonster::OnCollisionExit(Collider* _other)
{
}
