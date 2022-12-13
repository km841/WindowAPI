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
#include "CameraMgr.h"

HomingMissileEffect::HomingMissileEffect()
	: mAngleLimit(Math::DegreeToRadian(45.f))
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
		GameObject* target = 
			SceneMgr::GetInstance().GetCurScene()->GetNearestObject(Player::GetPlayer(), OBJECT_TYPE::MONSTER);

		// �߻��� �������� �� ���ư��ٰ�
		// Ÿ���� ���� ����

		// ���콺��ġ - �÷��̾� ��ġ

		if (nullptr != target)
		{
			MagicWandBullet* bullet = new MagicWandBullet;
			bullet->SetPos(GetPos());

			Vec2 mousePos = MOUSE_POS;
			Vec2 playerPos = RENDER_POS(Player::GetPlayer()->GetPos());

			Vec2 dirVec = mousePos - playerPos;
			dirVec.Norm();

			bullet->SetInitDirVector(dirVec);
			bullet->SetTarget(target);
			mBullets.push_back(bullet);
			EventRegisteror::GetInstance().CreateObject(bullet, bullet->GetType());
		}
	}

	if (IS_JUST_PRESSED(KEY::Q))
	{
		GameObject* target =
			SceneMgr::GetInstance().GetCurScene()->GetNearestObject(Player::GetPlayer(), OBJECT_TYPE::MONSTER);

		// �߻��� �������� �� ���ư��ٰ�
		// Ÿ���� ���� ����

		// ���콺��ġ - �÷��̾� ��ġ

		if (nullptr != target)
		{
			// 8����
			Vec2 dirArray[8] = {
				Vec2(-1, -1),
				Vec2(0, -1),
				Vec2(1, -1),
				Vec2(1, 0),
				Vec2(1, 1),
				Vec2(0, 1),
				Vec2(-1, 1),
				Vec2(-1, 0),
			};

			for (int i = 0; i < 8; ++i)
			{
				MagicWandBullet* bullet = new MagicWandBullet;
				bullet->SetPos(GetPos());
				bullet->SetInitDirVector(dirArray[i]);
				bullet->SetTarget(target);
				mBullets.push_back(bullet);
				EventRegisteror::GetInstance().CreateObject(bullet, bullet->GetType());
			}

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

		float initCurDuration = iter.operator*()->GetInitCurDuration();
		float initMaxDuration = iter.operator*()->GetInitMaxDuration();

		Vec2 bulletPos = iter.operator*()->GetPos();
		float bulletSpeed = iter.operator*()->GetBulletInfo().mSpeed;

		Vec2 dir = iter.operator*()->GetSpeedVector();
		if (Vec2(0.f, 0.f) == dir)
		{
			dir = iter.operator*()->GetInitDirVector();
		}

		if (initCurDuration < initMaxDuration)
		{
			// initDir �������� ���ư���
			Vec2 initDir = iter.operator*()->GetInitDirVector();

			iter.operator*()->SetSpeedVector(initDir);
			bulletPos += initDir * bulletSpeed * DT;
			initCurDuration += DT;
			iter.operator*()->SetInitCurDuration(initCurDuration);
		}

		else
		{
			Vec2 targetPos = iter.operator*()->GetTarget()->GetCollider()->GetPos();

			Vec2 targetVec = targetPos - bulletPos;

			// ����
			float curAngle = atan2(dir.y, dir.x);
			float targetAngle = atan2(targetVec.y, targetVec.x);



			if (curAngle > targetAngle)
			{
				if (curAngle - targetAngle > mAngleLimit)
				{
					dir = Math::RotateVector(dir, -mAngleLimit);
				}

				else
				{
					dir = Math::RotateVector(dir, Math::DegreeToRadian(-(curAngle - targetAngle)));
				}

			}
			else if (curAngle < targetAngle)
			{
				if (curAngle - targetAngle > mAngleLimit)
				{
					dir = Math::RotateVector(dir, mAngleLimit);
				}

				else
				{
					dir = Math::RotateVector(dir, Math::DegreeToRadian((curAngle - targetAngle)));
				}
			}
			
			bulletPos += dir * bulletSpeed * DT;
		}

		iter.operator*()->SetSpeedVector(dir);
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
	//for (int i = 0; i < mBullets.size(); ++i)
	//{
	//	if (nullptr != mBullets[i])
	//	{
	//		//delete mBullets[i];
	//		mBullets[i] = nullptr;
	//	}
	//}

}
