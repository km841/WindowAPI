#include "pch.h"
#include "MonsterBullet.h"
#include "Collider.h"
#include "CameraMgr.h"
#include "TimeMgr.h"
#include "Animator.h"
#include "Animation.h"

MonsterBullet::MonsterBullet()
{
	SetType(OBJECT_TYPE::MISSILE_FROM_MONSTER);
}

MonsterBullet::~MonsterBullet()
{
}

void MonsterBullet::Initialize()
{
	GameObject::Initialize();
}

void MonsterBullet::Update()
{
	GameObject::Update();

	if (IsDeadAnim())
	{
		Animator* animator = GetAnimator();
		if (nullptr != animator && 
			nullptr != animator->GetCurAnimation())
		{
			if (GetAnimator()->GetCurAnimation()->IsFinished())
			{
				SetObjState(OBJECT_STATE::DEAD);
			}
		}
	}

	else
	{
		// 화면 밖으로 날아가면 false
		if (CameraMgr::GetInstance().OutOfScreen(GetPos()))
		{
			Dead();
		}

		Vec2 bulletPos = GetPos();

		switch (GetBulletWayType())
		{
		case BULLET_WAY_TYPE::LINEAR:
		{
			Vec2 dir = GetDir();
			bulletPos += dir * mInfo.mSpeed * DT;
			SetPos(bulletPos);
		}
		break;
		case BULLET_WAY_TYPE::ROTATE:
		{
			MonsterBullet* stBullet = GetStandardBullet();
			if (nullptr != stBullet)
			{
				Vec2 stBulletPos = stBullet->GetPos();

				float angle = GetAngle();
				float radius = GetRadius();

				angle += 270.f * DT;
				float radian = Math::DegreeToRadian(angle);
				bulletPos.x = stBulletPos.x + radius * cos(radian);
				bulletPos.y = stBulletPos.y + radius * sin(radian);

				SetAngle(angle);
				SetPos(bulletPos);
			}
		}
		break;

		}
	}
}

void MonsterBullet::Render()
{
	GameObject::Render();
}

void MonsterBullet::OnCollision(Collider* _other)
{
}

void MonsterBullet::OnCollisionEnter(Collider* _other)
{
}

void MonsterBullet::OnCollisionExit(Collider* _other)
{
}

bool MonsterBullet::AllDeadChildBullet()
{
	bool deadFlag = true;

	for (int i = 0; i < mChildBullets.size(); ++i)
	{
		if (mChildBullets[i]->IsAlive())
			deadFlag = false;
	}

	return deadFlag;
}

void MonsterBullet::ChildColliderOn()
{
	for (int i = 0; i < mChildBullets.size(); ++i)
	{
		mChildBullets[i]->GetCollider()->SetEnable(true);
	}
}

void MonsterBullet::SetAllDeadAnimChildBullet()
{
	for (int i = 0; i < mChildBullets.size(); ++i)
	{
		if (mChildBullets[i]->IsAlive())
			mChildBullets[i]->Dead();
	}
}
