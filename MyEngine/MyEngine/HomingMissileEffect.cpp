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

		if (initCurDuration < initMaxDuration)
		{
			// initDir �������� ���ư���
			Vec2 initDir = iter.operator*()->GetInitDirVector();

			iter.operator*()->SetSpeedVector(initDir * bulletSpeed);
			bulletPos += initDir * bulletSpeed * DT;
			initCurDuration += DT;
			iter.operator*()->SetInitCurDuration(initCurDuration);
		}

		else
		{
			// ��ȸ�ϴ� ����ź

			//1. ���� ����
			//2. �ݽð���� ����ġ ����
			//3. �ð���� ����ġ ����

			// ������ ���� ���� ���� ���̰� �������
			// ���� ���� 5��
			Vec2 dir = {};

			Vec2 targetPos = iter.operator*()->GetTarget()->GetCollider()->GetPos();
			//dirVec = ���� ����

			// ���� ����
			// ���� ���ư��� ����.. �ֳ�?
			// ���͸� �ٷ� ������ ���� ������ �־�� ��
			Vec2 orgVec = iter.operator*()->GetSpeedVector();

			// ���� ĳ���͹��� �ӵ�����
			Vec2 dirVec = targetPos - bulletPos;
			dirVec.Norm();
			dirVec *= bulletSpeed;

			float rad = Math::DegreeToRadian(5.f);
			// �ð����

			// �ð���� ����ġ 
			Vec2 CW = {};
			Vec2 CCW = {};
			CW.x = cos(rad) * dirVec.x - sin(rad) * dirVec.y;
			CW.y = sin(rad) * dirVec.x + cos(rad) * dirVec.y;
			
			if (orgVec.Dot(dirVec) >= orgVec.Dot(CW))
			{
				dir = dirVec;
			}

			else
			{
				CCW.x = cos(rad) * dirVec.x + sin(rad) * dirVec.y;
				CCW.y = -sin(rad) * dirVec.x + cos(rad) * dirVec.y;

				// źȯ���� Target������ ��ġ����
				Vec2 tVec= CCW - targetPos;
				
				if (CW.Dot(tVec) >= CCW.Dot(tVec))
				{
					dir = CW;
				}
				else
				{
					dir = CCW;
				}
			}
			
			iter.operator*()->SetSpeedVector(dir);
			bulletPos += dir * DT;
		}

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
