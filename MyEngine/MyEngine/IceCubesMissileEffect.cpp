#include "pch.h"
#include "IceCubesMissileEffect.h"
#include "Player.h"
#include "IceBullet.h"
#include "EventRegisteror.h"
#include "TimeMgr.h"

IceCubesMissileEffect::IceCubesMissileEffect()
	: mMaxDuration(0.1f)
	, mCurDuration(0.f)
	, mMaxBulletCount(4.f)
	, mCurBulletCount(0.f)
{
}

IceCubesMissileEffect::~IceCubesMissileEffect()
{
}

void IceCubesMissileEffect::Initialize()
{
	MonsterMissileEffect::Initialize();
}

void IceCubesMissileEffect::Update()
{
	MonsterMissileEffect::Update();
}

void IceCubesMissileEffect::Render()
{
}

void IceCubesMissileEffect::Destroy()
{
}

bool IceCubesMissileEffect::Skill()
{
	// ������ ���� ��ġ���� IceBullet 3�� ��ȯ
	// ������ ����Ʈ�� �Բ� �߻�

	if (mMaxBulletCount < mCurBulletCount)
	{
		mCurBulletCount = 0.f;
		mCurDuration = 0.f;
		mPlayerDir = ZERO_VECTOR;
		return false;
	}

	else
	{
		Player* player = Player::GetPlayer();
		if (nullptr != player)
		{
			if (mMaxDuration < mCurDuration)
			{
				mCurBulletCount++;
				mCurDuration = 0.f;
				Vec2 playerPos = player->GetPos();
				Vec2 monsterPos = GetPos();
				Vec2 effectPos = GetPos();

				int randValue = (int)(rand() % 20);
				bool signValue = rand() % 2;

				
				if (mPlayerDir.IsZero())
				{
					mPlayerDir = playerPos - monsterPos;
					mPlayerDir.Norm();
				}

				float angle = atan2(mPlayerDir.y, mPlayerDir.x);

				if (signValue)
				{
					randValue = -randValue;
				}

				effectPos += (float)randValue;

				IceBullet* bullet = new IceBullet;
				bullet->SetDir(mPlayerDir);
				bullet->SetPos(effectPos);
				bullet->SetAngle(angle);
				bullet->SetBulletWayType(BULLET_WAY_TYPE::LINEAR);
				bullet->Initialize();

				EventRegisteror::GetInstance().CreateObject(bullet, bullet->GetType());
			}

			else
			{
				mCurDuration += DT;
			}

		}
	}


	return true;
}
