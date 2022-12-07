#include "pch.h"
#include "HomingMissileEffect.h"
#include "KeyMgr.h"
#include "MouseMgr.h"
#include "MagicWandBullet.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Player.h"
#include "TimeMgr.h"
#include "EventRegisteror.h"
#include "Collider.h"
#include "Monster.h"
#include "Animation.h"
#include "Animator.h"

HomingMissileEffect::HomingMissileEffect()
{

}

HomingMissileEffect::~HomingMissileEffect()
{
}

void HomingMissileEffect::Update()
{
	Effect::Update();
	// ��Ŭ���� ������ źȯ �߻�
	if (IS_JUST_LBUTTON_CLICKED)
	{
		// 
		MagicWandBullet* bullet = new MagicWandBullet;
		bullet->SetPos(GetPos());

		GameObject* target = 
			SceneMgr::GetInstance().GetCurScene()->GetNearestObject(Player::GetPlayer(), OBJECT_TYPE::MONSTER);
		
		if (nullptr != target)
		{
			bullet->SetTarget(target);
			mBullets.push_back(bullet);
			EventRegisteror::GetInstance().CreateObject(bullet, bullet->GetType());
		}
	}


	std::vector<MagicWandBullet*>::iterator iter = mBullets.begin();
	for (; iter != mBullets.end();)
	{
		// �÷��̾� ��ġ�� ���� �����̻���
		// Ÿ���� �������� ��
		// ���� ����� ���͸� ã�� �� ���Ϳ��� �Ÿ��� ����
		// Ÿ���� ������� ���ο� Ÿ������ ����
		// ���� ��ġ

		if (BULLET_STATE::DEAD_ANIM == iter.operator*()->GetBulletState())
		{
			++iter;
			continue;
		}

		if (BULLET_STATE::DEAD == iter.operator*()->GetBulletState())
		{
			EventRegisteror::GetInstance().DeleteObject(*iter);
			iter = mBullets.erase(iter);
			continue;
		}

		Monster* monster = static_cast<Monster*>(iter.operator*()->GetTarget());

		if (monster->IsDead())
		{
			// Ÿ���� ���� ��� Ÿ�� ����
			iter.operator*()->SetTarget(nullptr);
			GameObject* target =
				SceneMgr::GetInstance().GetCurScene()->GetNearestObject(Player::GetPlayer(), OBJECT_TYPE::MONSTER);
			if (nullptr != target)
				iter.operator*()->SetTarget(target);
		}

		// Ÿ���� ������ �Ҹ�
		if (nullptr == iter.operator*()->GetTarget())
		{
			iter.operator*()->SetBulletState(BULLET_STATE::DEAD_ANIM);
			iter.operator*()->GetAnimator()->SelectAnimation(L"LaraBulletHit", false);
			break;
		}
		
		// Ÿ���� ���⺤�͸� ���ؼ� �Ѿ��� �ӵ��� ����

		Vec2 bulletPos = iter.operator*()->GetPos();
		Vec2 targetPos = iter.operator*()->GetTarget()->GetCollider()->GetPos();
		Vec2 dirVec = targetPos - bulletPos;
		dirVec.Norm();

		float bulletSpeed = iter.operator*()->GetBulletInfo().mSpeed;
		bulletPos += dirVec * bulletSpeed * DT;
		iter.operator*()->SetPos(bulletPos);

		++iter;
	}
	
}

void HomingMissileEffect::Render()
{
	Effect::Render();
}

void HomingMissileEffect::Destroy()
{
	for (int i = 0; i < mBullets.size(); ++i)
	{
		if (nullptr != mBullets[i])
		{
			delete mBullets[i];
			mBullets[i] = nullptr;
		}
	}

}
