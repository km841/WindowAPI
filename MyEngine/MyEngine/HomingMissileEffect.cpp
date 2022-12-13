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
	// 좌클릭이 눌리면 탄환 발사
	if (IS_JUST_LBUTTON_CLICKED)
	{
		GameObject* target = 
			SceneMgr::GetInstance().GetCurScene()->GetNearestObject(Player::GetPlayer(), OBJECT_TYPE::MONSTER);

		// 발사한 방향으로 좀 날아갔다가
		// 타겟을 향해 돌진

		// 마우스위치 - 플레이어 위치

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

		// 발사한 방향으로 좀 날아갔다가
		// 타겟을 향해 돌진

		// 마우스위치 - 플레이어 위치

		if (nullptr != target)
		{
			// 8방향
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
		// 플레이어 위치에 따른 유도미사일
		// 타겟이 정해져야 함
		// 가장 가까운 몬스터를 찾고 그 몬스터와의 거리를 구함
		// 타겟이 사라지면 새로운 타겟으로 변경
		// 현재 위치

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
			// 타겟이 죽은 경우 타겟 변경
			iter.operator*()->SetTarget(nullptr);
			GameObject* target =
				SceneMgr::GetInstance().GetCurScene()->GetNearestObject(Player::GetPlayer(), OBJECT_TYPE::MONSTER);
			if (nullptr != target)
				iter.operator*()->SetTarget(target);
		}

		// 타겟이 없으면 소멸
		if (nullptr == iter.operator*()->GetTarget())
		{
			iter.operator*()->SetBulletState(BULLET_STATE::DEAD_ANIM);
			iter.operator*()->GetAnimator()->SelectAnimation(L"LaraBulletHit", false);
			break;
		}
		
		// 타겟의 방향벡터를 구해서 총알의 속도를 더함

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
			// initDir 방향으로 날아가기
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

			// 각도
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
